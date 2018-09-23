#include "TetrisMenu.h"
#include "../ScreenManager.h"
#include "../Collection.h"
#include <iostream>
#include "TetrisLoader.h"

/*
	Allows to switch through the menu.
*/
void TetrisGame::TetrisMenu::handleEvent(const sf::Event sfevent)
{
	int entryIndex;
	switch (sfevent.key.code)
	{
	case sf::Keyboard::Up:
		if (m_hover == 0)
			m_hover = ENTRYS(END - 1);
		else
			m_hover = ENTRYS(m_hover - 1);
		break;
	case sf::Keyboard::Down:
		entryIndex = ENTRYS((m_hover + 1)) % (END);
		m_hover = ENTRYS(abs(entryIndex));
		break;
	case sf::Keyboard::Return:
		m_currentState = ENTRYS(m_hover);
		m_running = false; // will invoke close()
		break;
	default:
		break;
	}
}


void TetrisGame::TetrisMenu::draw(sf::RenderWindow* window, sf::Font* font)
{
	sf::Text menus[END];
	sf::Sprite sprite; // used for background and text rendering
	sf::Texture texture;

	// todo => ioutils
	if (!texture.loadFromFile("bg.png"))
	{
		std::cerr << "[ERROR] [TetrisGame::TetrisMenu] loading bg picture failed" << std::endl;
	}
	menus[m_hover].setFillColor(sf::Color(255, 0, 0, 255));
	
	menus[PLAY].setString("Start game!");
	menus[PLAY].setPosition({ 280.f, 160.f });

	menus[SETTINGS].setString("Settings");
	menus[SETTINGS].setPosition({ 280.f, 220.f });

	menus[MAINMENU].setString("Main Menu");
	menus[MAINMENU].setPosition({ 280.f, 400.f });

	menus[EXIT].setString("Exit");
	menus[EXIT].setPosition({ 280.f, 460.f });

	sprite.setTexture(texture);
	sprite.setColor(sf::Color(255, 255, 255, 150));

	for (auto &menu : menus) {
		menu.setFont(*font);
		menu.setCharacterSize(50);
		window->draw(menu);
	}
	window->draw(sprite);
}

/*
	Returns the number of selected menu entry. The selected menu entry is stored in m_currentState. 
	In case of exit or main menu the defined codes in ICollectionEntry will be returned. 
*/
int TetrisGame::TetrisMenu::close()
{
	switch (m_currentState)
	{
	case EXIT:
		return ICollectionEntry::EXIT_APP;
		break;
	case MAINMENU:
		return ICollectionEntry::MAIN_MENU;
	case SETTINGS:
		return TetrisLoader::SETTINGS;
	default:
		return m_hover;
	}
}