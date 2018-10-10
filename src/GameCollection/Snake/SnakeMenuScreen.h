#pragma once
#include "../ICollectionScreen.h"
#include <SFML/Graphics.hpp>
#include "SnakeScreen.h"

namespace SnakeGame {

class SnakeMenuScreen : public GameCollection::ICollectionScreen {
private:
	/*
	 * Specify the menu entrys.
	 * The entrys are the Same edsd
	 */
	enum ENTRYS { PLAY = 0, SETTINGS = 1, MAINMENU=2, EXIT = 3, END = 4 };

	const std::string entry_names[END] = { "Start Game!", "Highscores", "Main Menu", "Exit" };

	/*
	 * Specify the menu entry which is currently focused.
	 */
	ENTRYS m_hover = ENTRYS::PLAY;
	sf::Texture m_background;


	ICollectionScreen** entryScreens[END - 2];
	SnakeScreen* m_snakeGame;


public:
	static constexpr char s_BACKGROUND_PATH[] = "static/bg.jpeg";

	SnakeMenuScreen();
	virtual ~SnakeMenuScreen();

	void handleEvent(const sf::Event sfevent);
	void draw(sf::RenderWindow* window, sf::Font* font);
	int close(ICollectionScreen** screen);
};

} /* namespace SnakeGame */
