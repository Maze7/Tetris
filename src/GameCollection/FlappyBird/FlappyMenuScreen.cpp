#include "FlappyMenuScreen.h"

namespace FlappyBirdGame {

FlappyMenuScreen::FlappyMenuScreen() : m_flappyGame(nullptr) {
	entryScreens[PLAY] = (ICollectionScreen**) &m_flappyGame;
}

FlappyMenuScreen::~FlappyMenuScreen() {
	delete m_flappyGame;
}

void FlappyMenuScreen::handleEvent(const sf::Event sfevent) {
	int entryIndex;
	switch (sfevent.key.code) {
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
		if (m_hover == 0)
			m_hover = ENTRYS(END - 1);
		else
			m_hover = ENTRYS(m_hover - 1);
		break;
	case sf::Keyboard::S:
	case sf::Keyboard::Down:
		entryIndex = ENTRYS((m_hover + 1)) % (END);
		m_hover = ENTRYS(abs(entryIndex));
		break;
	case sf::Keyboard::Space:
	case sf::Keyboard::Return:
		if (m_hover == PLAY) {
			if (m_flappyGame == nullptr) {
				m_flappyGame = new FlappyBirdScreen();
			} else if (m_flappyGame->getGameState() == FlappyBirdScreen::GAMEOVER){
				delete m_flappyGame;
				m_flappyGame = new FlappyBirdScreen();
			}
			m_flappyGame->setGameState(FlappyBirdScreen::PLAYING);
		}
		m_running = false; // will invoke close()
		break;
	case sf::Keyboard::Delete:
		if (m_hover == PLAY) {
			delete m_flappyGame;
			m_flappyGame = nullptr;
		}
		break;
	default:
		break;
	}

}
void FlappyMenuScreen::draw(sf::RenderWindow* window, sf::Font* font) {
		sf::Text menus[END];
		sf::Sprite sprite; // used for background and text rendering

		sprite.setTexture(m_background);
		sprite.setColor(sf::Color(255, 255, 255, 150));
		sf::Vector2f pos(280.f, 110.f);

		for (unsigned int i = 0; i < END; i++) {
			if (i == ENTRYS::MAINMENU) {
				pos.y = pos.y + 130;
			}

			// show different text during gameplay
			if (i == PLAY
				&& m_flappyGame != nullptr
				&& m_flappyGame->getGameState() == FlappyBirdScreen::PLAYING) {
				menus[PLAY] = sf::Text ("Continue", *font, 50);

				sf::Text text("(press <DELETE> for reset)", *font, 20);
				text.setPosition({ 440.f, 180.f });
				window->draw(text);
			} else {
				menus[i] = sf::Text(entry_names[i], *font, 50);
			}

			if (m_hover == i) {
				menus[i].setFillColor(sf::Color(255, 0, 0, 255));
			}
			pos.y = pos.y + 60;
			menus[i].setPosition(pos);
			window->draw(menus[i]);
		}
		window->draw(sprite);
}

int FlappyMenuScreen::close(ICollectionScreen** screen) {
	switch (m_hover) {
	case MAINMENU:
		return MAIN_MENU;
		break;
	case EXIT:
		return EXIT_SUCCESS;
		break;
	default:
		*screen = *entryScreens[m_hover];
		return CONTINUE;
		break;
	}
}

} /* namespace FlappyBirdGame */
