#include "TetrisWindow.h"
namespace TetrisGame
{

	sf::RenderWindow* const initSFWindow(sf::RenderWindow* window) {
	
		static sf::RenderWindow* m_window = nullptr;

		if (m_window == nullptr)
			m_window = window;

		return m_window;
	}

	sf::RenderWindow* const getSFWindow()
	{
		return TetrisGame::initSFWindow(nullptr);
	}
}