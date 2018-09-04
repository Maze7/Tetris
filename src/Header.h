#pragma once
#include <SFML\Graphics.hpp>
namespace TetrisGame
{

	// Todo private bzw zugriff beschränken
	static sf::RenderWindow* m_window;

	inline const sf::RenderWindow* getWindow() {
		return m_window;
	}

	inline void setWindow(sf::RenderWindow& window) {
		m_window = &window;
	}
}