#include "MenuScreen.h"

#include "../Collection.h"
#include <iostream>
#include "TetrisLoader.h"

constexpr char TetrisGame::MenuScreen::s_BACKGROUND_PATH[];

TetrisGame::MenuScreen::MenuScreen() : m_score(TetrisScore())
{
	//Load background. Dont do it inside the draw loop!
	// Use the defined path to the background picture
	m_background = sf::Texture();
	m_currentState = PLAY;
	if (!m_background.loadFromFile(s_BACKGROUND_PATH))
	{
		std::cerr << "[ERROR] [TetrisGame::TetrisMenu] loading bg picture failed" << std::endl;
	}
}

/*
	Allows to switch through the menu.
*/
void TetrisGame::MenuScreen::handleEvent(const sf::Event sfevent)
{
	int entryIndex;
	switch (sfevent.key.code)
	{
	case sf::Keyboard::H:
		if(OS_Windows)
			system("notepad.exe Tetris\\helptext_Tetris.txt");
		break;
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
		m_currentState = ENTRYS(m_hover);
		m_running = false; // will invoke close()
		break;
	case sf::Keyboard::Delete:
		if (m_hover == PLAY) {
			m_currentState = ENTRYS(m_hover);
			TetrisLoader::erase(TetrisLoader::GAME);
		}
		break;
	default:
		break;
	}
}


void TetrisGame::MenuScreen::draw(sf::RenderWindow* window, sf::Font* font)
{
	sf::Text menus[END];
	sf::Sprite sprite; // used for background and text rendering

	sf::Text helpNote("Press <H> for help text", *font, 35);
	helpNote.setPosition( 280.f, (window->getSize().y - 50) * 1.f);
	window->draw(helpNote);

	sprite.setTexture(m_background);
	sprite.setColor(sf::Color(255, 255, 255, 150));
	sf::Vector2f pos(280.f, 110.f);

	for (unsigned int i = 0; i < END; i++) {
		if (i == ENTRYS::MAINMENU)
			pos.y = pos.y + 130;

		// show different text during gameplay
		if (i == PLAY 
			&& TetrisLoader::contains(TetrisLoader::GAME)
			&& (TetrisLoader::getGame()->getGameState() == GameScreen::PAUSED || TetrisLoader::getGame()->getGameState() == GameScreen::PLAYING) )
		{
			menus[PLAY] = sf::Text ("Continue", *font, 50);

			sf::Text text("(press <DELETE> for reset)", *font, 20);
			text.setPosition({ 440.f, 180.f });
			window->draw(text);
		}
		else {
			menus[i] = sf::Text(entry_names[i], *font, 50);
		}

		if (m_hover == i)
			menus[i].setFillColor(sf::Color(255, 0, 0, 255));

		pos.y = pos.y + 60;
		menus[i].setPosition(pos);
		window->draw(menus[i]);
	}
	window->draw(sprite);
}

/*
	Returns the number of selected menu entry. The selected menu entry is stored in m_currentState. 
	In case of exit or main menu the defined codes in ICollectionEntry will be returned. 
*/
int TetrisGame::MenuScreen::close(ICollectionScreen** screen)
{
	switch (m_currentState)
	{
	case EXIT:
		return EXIT_SUCCESS;
		break;
	case MAINMENU:
		return MAIN_MENU;
		break;
	case SETTINGS:
		// create new settings if needed
		if (!TetrisLoader::contains(TetrisLoader::SETTINGS)) {
			TetrisLoader::addScreen(TetrisLoader::SETTINGS, new SettingsScreen());
		}
		*screen = *TetrisLoader::getScreen(TetrisLoader::SETTINGS);
		return CONTINUE;
		break;
	case HIGHSCORES:
		if (!TetrisLoader::contains(TetrisLoader::SCORE)) {
			TetrisLoader::addScreen(TetrisLoader::SCORE, new ScoreScreen(m_score));
		}
		*screen = *TetrisLoader::getScreen(TetrisLoader::SCORE);
		return CONTINUE;
	case PLAY:
	{ // new scope, needed for gameScreen

		if (!TetrisLoader::contains(TetrisLoader::GAME)) {
			TetrisLoader::addScreen(TetrisLoader::GAME, new GameScreen(m_score));
		}
		ICollectionScreen** gameScreen = TetrisLoader::getScreen(TetrisLoader::GAME);

		if (TetrisLoader::getGame()->getGameState() == GameScreen::GAMEOVER) { // if game is not running right now, create a new one and starts to play
			delete *gameScreen;
			m_score.reset();
			*gameScreen = new GameScreen(m_score); // let pointer point to a new game
			TetrisLoader::getGame()->setGameState(GameScreen::PLAYING);
		}
		*screen = *TetrisLoader::getScreen(TetrisLoader::GAME); // open game
	}
		return CONTINUE;

		break;
	default:
		return EXIT_FAILURE;
		break;
	}
}
