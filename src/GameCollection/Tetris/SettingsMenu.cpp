#include "SettingsMenu.h"
#include "TetrisLoader.h"
#include <iostream>

TetrisGame::SettingsMenu::SettingsMenu()
{
	// Load Background picture. Use same as tetris menu.
	m_background = sf::Texture();
	if (!m_background.loadFromFile(TetrisGame::TetrisMenu::s_BACKGROUND_PATH))
	{
		std::cerr << "[ERROR] [TetrisGame::SettingsMenu] loading bg picture failed" << std::endl;
	}
}

void TetrisGame::SettingsMenu::handleEvent(const sf::Event sfevent)
{
	int newHover;
	switch (sfevent.key.code)
	{
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
		if (m_hover == 0)
			m_hover = ENTRYS(END - 1);
		else
			m_hover = ENTRYS(m_hover - 1);
		break;

	case sf::Keyboard::S:
	case sf::Keyboard::Down:
		newHover = (m_hover + 1) % END;
		m_hover = ENTRYS(newHover);
		break;

	case sf::Keyboard::Escape:
		m_hover = BACK;
	case sf::Keyboard::Return:
		//TODO
		if (m_hover == BACK)
			m_running = false;
		break;
	
	case sf::Keyboard::A:
	case sf::Keyboard::Left:
		if (m_hover == SOUND_VOLUME && m_volume > 0)
			m_volume--;
		break;

	case sf::Keyboard::D:
	case sf::Keyboard::Right:
		if (m_hover == SOUND_VOLUME && m_volume < MAX_VOLUME)
			m_volume++;
		break;
	}
}

void TetrisGame::SettingsMenu::draw(sf::RenderWindow* window, sf::Font* font)
{
	sf::Vector2f pos(280.f, 160.f);
	sf::Text menus[END];
	sf::RectangleShape volumeBars[10];

	for (unsigned int i = 0; i < END; i++) {
		menus[i] = sf::Text(entryNames[i], *font, 50);
		menus[i].setPosition(pos);
		pos.y = pos.y + 60;
		if (i == m_hover) {
			menus[i].setFillColor(sf::Color(255,0,0,255));
		}
		if (i == SOUND_VOLUME) {
			pos.y = pos.y + 20;
			int x = pos.x;
			for (unsigned int j = 1; j < m_volume; j++) {
				volumeBars[j].setFillColor(sf::Color::White);
				volumeBars[j].setSize(sf::Vector2f(35,25));
				volumeBars[j].setOutlineThickness(1);
				volumeBars[j].setOutlineColor(sf::Color::Black);
				volumeBars[j].setPosition(sf::Vector2f(x, pos.y));
				x = x + 35;
				window->draw(volumeBars[j]);
			}
			pos.y = pos.y + 60;
		}
		window->draw(menus[i]);
	}
	sf::Sprite sprite;
	sprite.setTexture(m_background);
	sprite.setColor(sf::Color(255, 255, 255, 150));
	window->draw(sprite); // background opacity
}

int TetrisGame::SettingsMenu::close()
{
	std::vector<ICollectionEntry*>* modulScreens = GameCollection::Collection::getEntrys()->at(TetrisLoader::MODUL_NAME);
	TetrisGame::Game* game = dynamic_cast<Game*>(modulScreens[0][TetrisLoader::GAME]);
	// game->setVolume or smth like this.
	// game set startlevel
	switch (m_hover)
	{
	case BACK:
		return TetrisLoader::MENU;
		break;
	default: // should never reached => avoid compiler warning
		return EXIT_APP;
		break;
	}
}
