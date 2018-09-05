#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"


namespace TetrisGame
{
	const sf::RenderWindow* const initSFWindow(sf::RenderWindow* window) {
		static bool init;
		static sf::RenderWindow* m_window;

		if (!init && window != nullptr) {
			m_window = window;
			init = true;
		}
		return m_window;
	}

	const sf::RenderWindow* const getSFWindow() {
		return TetrisGame::initSFWindow(nullptr);
	}
}
