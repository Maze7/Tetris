#pragma once
#include "../ICollectionEntry.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

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

	public:
		TetrisMenu() {};
		~TetrisMenu() {};

		void handleEvent(const sf::Event sfevent);
		void draw(sf::RenderWindow* window, sf::Font* font);
		int close();
	};
}