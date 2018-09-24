#include "TetrisMenu.h"
#include "../Collection.h"
#include <iostream>
#include "TetrisLoader.h"

TetrisGame::TetrisMenu::TetrisMenu() 
{
	//Load background. Dont do it inside the draw loop!
	// Use the defined path to the background picture
	m_background = sf::Texture();
	if (!m_background.loadFromFile(s_BACKGROUND_PATH))
	{
		std::cerr << "[ERROR] [TetrisGame::SettingsMenu] loading bg picture failed" << std::endl;
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

	menus[m_hover].setFillColor(sf::Color(255, 0, 0, 255));
	
	if (getGame()->getGameState() == Game::PLAYING) {
		menus[PLAY].setString("Continue");
		sf::Text text;
		text.setPosition({ 440.f, 180.f });
		text.setFont(*font);
		text.setCharacterSize(20);
		text.setString("(press <DELETE> for reset)");
		window->draw(text);
	}
	else {
		menus[PLAY].setString("Start game!");
	}
	menus[PLAY].setPosition({ 280.f, 160.f });

	menus[SETTINGS].setString("Settings");
	menus[SETTINGS].setPosition({ 280.f, 220.f });

	menus[MAINMENU].setString("Main Menu");
	menus[MAINMENU].setPosition({ 280.f, 400.f });

	menus[EXIT].setString("Exit");
	menus[EXIT].setPosition({ 280.f, 460.f });

	//Local struct
	struct TextPos {
		float x;
		float y;
		sf::Vector2f v = { x, y  - 50};
	};

	sf::Text helpNote("Press <H> for help text", *font, 35);
	TextPos pos = { 280.f, window->getSize().y };
	helpNote.setPosition(pos.v);
	window->draw(helpNote);

	sprite.setTexture(m_background);
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

