#include "TetrisGame.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Tetris");
	TetrisGame::initSFWindow(&window);

	system("PAUSE");
}


