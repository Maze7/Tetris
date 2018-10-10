#pragma once
#include <SFML/Graphics.hpp>

#include "../ICollectionScreen.h"
#include "GameScreen.h"

/*
 * Check the platform and define it to OS_Windows.
 * OS_Windows = 1 if platform is windows
 * OS_Windows = 0 if platform is unix (like Linux)
 */
#ifdef __unix__                   
	constexpr bool OS_Windows = 0;
#elif defined(_WIN32) || defined(WIN32)
	constexpr bool OS_Windows = 1;
#endif

namespace TetrisGame
{
	class MenuScreen : public GameCollection::ICollectionScreen
	{
	private:
		/*
		 * Specify the menu entrys.
		 * The entrys are the Same edsd
		 */
		enum ENTRYS { PLAY = 0, SETTINGS = 1, HIGHSCORES=2, MAINMENU=3, EXIT = 4, END = 5 };

		const std::string entry_names[END] = { "Start Game!", "Settings", "Highscores", "Main Menu", "Exit" };

		/* 
		 * Specify the current
		 */
		ENTRYS m_currentState;

		/*
		 * Specify the menu entry which is currently focused. 
		 */
		ENTRYS m_hover = ENTRYS::PLAY;

		sf::Texture m_background;

		TetrisScore m_score;

	public:
		static constexpr char s_BACKGROUND_PATH[] = "static/bg.jpeg";

		MenuScreen();
		~MenuScreen() {};

		void handleEvent(const sf::Event sfevent);
		void draw(sf::RenderWindow* window, sf::Font* font);
		int close(ICollectionScreen** screen);
	};
}
