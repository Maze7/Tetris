#include "SettingsScreen.h"

#include "TetrisLoader.h"
#include <iostream>

TetrisGame::SettingsScreen::SettingsScreen()
{
	// Load Background picture. Use same as tetris menu.
	m_background = sf::Texture();
	if (!m_background.loadFromFile(TetrisGame::MenuScreen::s_BACKGROUND_PATH))
	{
		std::cerr << "[ERROR] [TetrisGame::SettingsMenu] loading bg picture failed" << std::endl;
	}
}

void TetrisGame::SettingsScreen::handleEvent(const sf::Event sfevent)
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
		// instant return
	case sf::Keyboard::Space:
	case sf::Keyboard::Return:
		//TODO
		if (m_hover == BACK)
			m_running = false;
		break;
	
	case sf::Keyboard::A:
	case sf::Keyboard::Left:
		if (m_hover == SOUND_VOLUME && m_volume > 0)
			m_volume--;
		else if (m_hover == DIFFICULTY) 
			m_difficulty = --m_difficulty % DIFFICULTY_SIZE;
		break;

	case sf::Keyboard::D:
	case sf::Keyboard::Right:
		if (m_hover == SOUND_VOLUME && m_volume < MAX_VOLUME)
			m_volume++;
		if (m_hover == DIFFICULTY)
			m_difficulty = ++m_difficulty % DIFFICULTY_SIZE;
		break;
	}
}

void TetrisGame::SettingsScreen::draw(sf::RenderWindow* window, sf::Font* font)
{
	sf::Vector2f pos(280.f, 160.f);
	sf::Text menus[END];
	sf::RectangleShape volumeBars[MAX_VOLUME];
	sf::Text diffTexts[DIFFICULTY_SIZE] = {
			sf::Text("0", *font, 35),
			sf::Text(std::to_string(m_difficultyIntervall),*font, 35),
			sf::Text(std::to_string((2*m_difficultyIntervall)), *font, 35),
			sf::Text(std::to_string((3*m_difficultyIntervall)), *font, 35)
	};

	for (unsigned int i = 0; i < END; i++) {
		menus[i] = sf::Text(entryNames[i], *font, 50);
		menus[i].setPosition(pos);
		pos.y = pos.y + 60;
		if (i == m_hover) {
			menus[i].setFillColor(sf::Color(255,0,0,255));
		}
		if (i == SOUND_VOLUME) {
			pos.y = pos.y + 20;
			unsigned int x = pos.x;
			for (unsigned int j = 0; j < m_volume; j++) {
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
		else if (i == DIFFICULTY)  {
			unsigned int x = pos.x; // copy
			for (unsigned j = 0; j < DIFFICULTY_SIZE; j++) {
				diffTexts[j].setPosition(x, pos.y);
				x = x + 75;
				if (m_difficulty == j) {
					diffTexts[j].setFillColor({ 255, 0, 0, 255 });
				}
				window->draw(diffTexts[j]);
			}
			pos.y = pos.y + 40; // make gap wider
		}

		window->draw(menus[i]);
	}
	sf::Sprite sprite;
	sprite.setTexture(m_background);
	sprite.setColor(sf::Color(255, 255, 255, 150));
	window->draw(sprite); // background opacity
}

int TetrisGame::SettingsScreen::close(ICollectionScreen** screen)
{

	if (TetrisLoader::contains(TetrisLoader::GAME)) {
		TetrisLoader::getGame()->setSoundVolume(getSoundVolume());
	}
	switch (m_hover)
	{
	case BACK:
		*screen = *TetrisLoader::getScreen(TetrisLoader::MENU);
		return CONTINUE;
		break;
	default: // should never reached => avoid compiler warning
		return EXIT_APP;
		break;
	}
}

const unsigned int TetrisGame::SettingsScreen::getDifficulty() {
	return m_difficulty * m_difficultyIntervall;
}

/*
 * Returns a sound volume from 0 - 100 (%)
 * Directly parse to sfml sound is possible.
 */
float TetrisGame::SettingsScreen::getSoundVolume() {
	return m_volume * 10.f;
}
