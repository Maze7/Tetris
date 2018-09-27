#pragma once
#include "../ICollectionEntry.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

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
	class TetrisMenu : public GameCollection::ICollectionEntry
	{
	private:
		/*
		 * Specify the menu entrys.
		 * The entrys are the Same 
		 */
		enum ENTRYS { PLAY = 1, SETTINGS = 2, MAINMENU=3, EXIT = 4, END = 5 };

		/* 
		 * Specify the current
		 */
		ENTRYS m_currentState;

		/*
		 * Specify the menu entry which is currently focused. 
		 */
		ENTRYS m_hover = ENTRYS::PLAY;

		sf::Texture m_background;

	public:
		static constexpr char s_BACKGROUND_PATH[] = "test.jpeg";

		TetrisMenu();
		~TetrisMenu() {};

		void handleEvent(const sf::Event sfevent);
		void draw(sf::RenderWindow* window, sf::Font* font);
		int close();

		Game* getGame();
	};
}