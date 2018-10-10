#pragma once
#include "../ICollectionScreen.h"
#include <SFML/Graphics.hpp>
#include "FlappyBirdScreen.h"

namespace FlappyBirdGame {

class FlappyMenuScreen : public GameCollection::ICollectionScreen {
private:
	/*
	 * Specify the menu entrys.
	 * The entrys are the Same edsd
	 */
	enum ENTRYS { PLAY = 0, MAINMENU=1, EXIT = 2, END = 3 };

	const std::string entry_names[END] = { "Start Game!","Main Menu", "Exit" };

	/*
	 * Specify the menu entry which is currently focused.
	 */
	ENTRYS m_hover = ENTRYS::PLAY;
	sf::Texture m_background;


	ICollectionScreen** entryScreens[END - 2];
	FlappyBirdScreen* m_flappyGame;



public:
	static constexpr char s_BACKGROUND_PATH[] = "static/bg.jpeg";

	FlappyMenuScreen();
	virtual ~FlappyMenuScreen();

	void handleEvent(const sf::Event sfevent);
	void draw(sf::RenderWindow* window, sf::Font* font);
	int close(ICollectionScreen** screen);
};

} /* namespace FlappyBirdGame */
