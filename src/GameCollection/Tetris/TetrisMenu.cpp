#include "TetrisMenu.h"
#include "../Collection.h"
#include <iostream>
#include "TetrisLoader.h"

constexpr char TetrisGame::TetrisMenu::s_BACKGROUND_PATH[];

TetrisGame::TetrisMenu::TetrisMenu() 
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
void TetrisGame::TetrisMenu::handleEvent(const sf::Event sfevent)
{
	int entryIndex;
	switch (sfevent.key.code)
	{
	case sf::Keyboard::H:
		if(OS_Windows)
			system("notepad.exe Tetris\\helptext_Tetris.txt");
		break;
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
	case sf::Keyboard::Delete:
		if (m_hover == PLAY) {
			m_currentState = ENTRYS(m_hover);
			getGame()->setGameState(Game::GAMEOVER);
		}
		break;
	default:
		break;
	}
}


void TetrisGame::TetrisMenu::draw(sf::RenderWindow* window, sf::Font* font)
{
	sf::Text menus[END];
	sf::Sprite sprite; // used for background and text rendering

	//menus[m_hover].setFillColor(sf::Color(255, 0, 0, 255));
	//menus[PLAY].setPosition({ 280.f, 160.f });

	//menus[SETTINGS].setString("Settings");
	//menus[SETTINGS].setPosition({ 280.f, 220.f });

	//menus[MAINMENU].setString("Main Menu");
	//menus[MAINMENU].setPosition({ 280.f, 400.f });

	//menus[EXIT].setString("Exit");
	//menus[EXIT].setPosition({ 280.f, 460.f });

	sf::Text helpNote("Press <H> for help text", *font, 35);
	helpNote.setPosition( 280.f, (window->getSize().y - 50) * 1.f);
	window->draw(helpNote);

	sprite.setTexture(m_background);
	sprite.setColor(sf::Color(255, 255, 255, 150));
	sf::Vector2f pos(280.f, 160.f);

	for (unsigned int i = 0; i < END; i++) {
		if (i == ENTRYS::MAINMENU)
			pos.y = pos.y + 130;
		
		if (i == PLAY && getGame()->getGameState() == Game::PLAYING) { // show different text during gameplay
			menus[PLAY] = sf::Text ("Continue", *font, 50);

			sf::Text text("(press <DELETE> for reset)", *font, 20);
			text.setPosition({ 440.f, 180.f });
			window->draw(text);
		}
		else {
			menus[i] = sf::Text(entry_names[i], *font, 50);
		}

		if (m_hover == i)
			menus[i].setFillColor(sf::Color(255, 0, 0, 150));

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
int TetrisGame::TetrisMenu::close()
{
	Game* game = getGame();
	switch (m_currentState)
	{
	case EXIT:
		return ICollectionEntry::EXIT_APP;
		break;
	case MAINMENU:
		return ICollectionEntry::MAIN_MENU;
		break;
	case SETTINGS:
		return TetrisLoader::SETTINGS;
		break;
	case HIGHSCORES:
		return TetrisLoader::SCORE;
		break;
	case PLAY:
		// if game is not running right now, create a new one and starts to play
		if (game->getGameState() != Game::PLAYING) {
			*game = Game(); // new game
			game->setGameState(Game::PLAYING);
		}
		return TetrisLoader::GAME;
		break;
	default:
		return m_hover;
		break;
	}
}

TetrisGame::Game* TetrisGame::TetrisMenu::getGame()
{
	std::vector<ICollectionEntry*>* modulScreens = GameCollection::Collection::getEntrys()->at(TetrisLoader::MODUL_NAME);
	Game* game = dynamic_cast<Game*>(modulScreens[0][TetrisLoader::GAME]);
	return game;
}

