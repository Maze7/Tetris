#include "TetrisGame.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Tetris");
	TetrisGame::initSFWindow(&window);
	TetrisGame::Playfield playf{};
	TetrisGame::Tetromino::TETROMINO_TYPE type = TetrisGame::Tetromino::J;
	TetrisGame::Tetromino tetro(type, TetrisGame::Tetromino::PLAYFIELD_POS);
	playf.draw(tetro);

	system("PAUSE");
}

