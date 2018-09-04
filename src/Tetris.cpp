#include <iostream>
#include <SFML/Graphics.hpp>

namespace TetrisGame
{
	// Todo private bzw zugriff beschränken
	static sf::RenderWindow* m_window; 

	const sf::RenderWindow* getWindow() {
		return m_window;
	}

	void setWindow(sf::RenderWindow& window) {
		m_window = &window;
	}
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Tetris");
	TetrisGame::setWindow(window);

	int zahl = 4;
	test(zahl);
}

void test(int& zahl) {
	int& zahl = zahl;
}


