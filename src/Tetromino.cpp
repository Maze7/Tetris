#include "Tetromino.h"

// 	enum TETROMINO_TYPE { I=0, J=1, L=2, O=3, S=4, T=5, Z=6, END=7 };
const TetroShape TetrisGame::Tetromino::SHAPE_DATA[TetrisGame::Tetromino::END][4] =
{
	{ // TetrisGame::Tetromino::I
		{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		},{
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0}
		}
	}, 
	{ // TetrisGame::Tetromino::J
		{
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		}, {
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{1, 1, 0, 0},
			{0, 0, 0, 0}
		}, {
			{1, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		}, {
			{1, 1, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{0, 0, 0, 0}
		}
	},
	{ // TetrisGame::Tetromino::L
		{
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{1, 0, 0, 0},
			{0, 0, 0, 0}
		}, {
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0}
		}, {
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0}
		}, {
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 0, 0, 0}
		}
	},
	{ // TetrisGame::Tetromino::O
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		}
	}, 
	{ // TetrisGame::Tetromino::S
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{1, 1, 0, 0},
			{0, 0, 0, 0},
		}, {
			{1, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0},
		}
	},
	{ // TetrisGame::Tetromino::T
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0}
		}, {
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0}
		}, {
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 1, 0, 0}
		}, {
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 0, 0}
		}
	},
	{ // TetrisGame::Tetromino::Z
		{
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0},
		}, {
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0},
		}
	}
};

/*
	Defines the tetromino colors according to their shapes.
	Should be used to get the color of an active tetromino, i.e when drawing
	it in the Playfield. 

	Example usage:
	sf::Color color = TetrisGame::Tetromino::SHAPE_COLORS[tetromino.getType()];

*/
const sf::Color TetrisGame::Tetromino::SHAPE_COLORS[TETROMINO_TYPE::END] =
{
	sf::Color::Cyan,				// I
	sf::Color::Blue,				// J
	sf::Color(255, 165, 0, 255),	// L
	sf::Color::Yellow,				// O
	sf::Color::Green,				// S
	sf::Color::Magenta,				// T
	sf::Color::Red					// Z
};



TetrisGame::Tetromino::~Tetromino()
{
}

