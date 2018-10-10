#include "MenuScreen.h"
namespace SnakeGame {

MenuScreen::MenuScreen() : m_snakeGame(nullptr) {
	entryScreens[PLAY] = (ICollectionScreen**) &m_snakeGame;
}

MenuScreen::~MenuScreen() {
	delete m_snakeGame;
}

void MenuScreen::handleEvent(const sf::Event sfevent) {
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
			if (m_snakeGame == nullptr) {
				m_snakeGame = new SnakeScreen();
			}
			m_snakeGame->setGameState(SnakeScreen::PLAYING);
		}
		m_running = false; // will invoke close()
		break;
	case sf::Keyboard::Delete:
		if (m_hover == PLAY) {
			delete m_snakeGame;
			m_snakeGame = nullptr;
		}
		break;
	default:
		break;
	}

}
void MenuScreen::draw(sf::RenderWindow* window, sf::Font* font) {
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
				&& m_snakeGame != nullptr
				&& m_snakeGame->getGameState() == SnakeScreen::PLAYING) {
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

int MenuScreen::close(ICollectionScreen** screen) {
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

} /* namespace SnakeGame */
