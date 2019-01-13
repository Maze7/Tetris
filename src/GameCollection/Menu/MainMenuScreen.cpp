#include "MainMenuScreen.h"
#include <iostream>

/*
	Constructor of MenuEnry. 
	It puts all keywords (strings) of s_entrys into m_entryNames. 
	This vector will needed to display the names of the different module to the main menu. 
*/
MainMenuScreen::MainMenuScreen() {
	const GameCollection::CollectionEntrys* const allEntrys = GameCollection::Collection::getEntrys();

	for (auto const& i : *allEntrys) {
		m_entryNames.push_back(i.first);
	}
	if (!m_background.loadFromFile("static/bg.jpeg")) {
		std::cerr << "[ERROR] [MainMenuScreen] loading bg picture failed" << std::endl;
	}

	m_entryNames.push_back("Exit");
	m_hover = 0;
}

void MainMenuScreen::handleEvent(const sf::Event sfevent) {
	switch (sfevent.key.code) {
	case sf::Keyboard::H:
		if(OS_Windows) {
			system("notepad.exe static\\helptext.txt");
		} else if(OS_Mac) {
			system("open static/helptext.txt");
		} else {
			system("xdp-open static/helptext.txt");
		}
		break;
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
		if (m_hover == 0) {
			m_hover = m_entryNames.size() - 1;
		} else {
			m_hover--;
		}
		break;
	case sf::Keyboard::S:
	case sf::Keyboard::Down:
		m_hover = ++m_hover % m_entryNames.size();
		break;
	case sf::Keyboard::Space:
	case sf::Keyboard::Return:
		m_currentName = m_entryNames[m_hover];
		m_running = false;
		break;
	}
}

void MainMenuScreen::draw(sf::RenderWindow* window, sf::Font* font) {
	sf::Sprite sprite; // used for background and text rendering
	sprite.setTexture(m_background);
	sprite.setColor(sf::Color(255, 255, 255, 150));

	sf::Text helpNote("Press <H> for help text", *font, 35);
	helpNote.setPosition( 280.f, (window->getSize().y - 50) * 1.f);
	window->draw(helpNote);

	std::vector<sf::Text> menus;
	sf::Vector2f pos = { 280.f, 160.f };

	int counter = 0;
	for (auto const& name : m_entryNames) {
		sf::Text menu(name, *font, 50);
		pos.y = pos.y + 50;
		menu.setPosition(pos);

		if (counter == m_hover) {
			menu.setFillColor(sf::Color(255, 0, 0, 255));
			// sets the current selected menu entry to red.
		}
		window->draw(menu);
		menus.push_back(menu);
		counter++;
	}
	window->draw(sprite);
}

const std::string& MainMenuScreen::getCurrentName() {
	return m_currentName;
}

int MainMenuScreen::close(ICollectionScreen** screen) {
	if (m_currentName == "Exit") {
		return EXIT_APP;
	} else {
		*screen = GameCollection::Collection::getEntrys()->at(m_currentName);
		return CONTINUE;
	}
}
