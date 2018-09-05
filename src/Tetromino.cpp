#include "Tetromino.h"

// 	enum TETROMINO_TYPE { I=0, J=1, L=2, O=3, S=4, T=5, Z=6, END=7 };
/*

*/
const TetrisGame::Tetromino::TetroShape TetrisGame::Tetromino::SHAPE_DATA[TetrisGame::Tetromino::END][4] =
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

/*
	Defines the number of different rotations of one Tetromino type.
	The defined number has to be equal to the size of the different arrays
	of one shape. Use this method if you want to know, how many 
	different rotation on Tetromino type have.

	Example Usage:
	if (m_rotation < SHAPE_SIZE[m_type])
		// it is valid to rotate
	else if (m_rotation >= SHAPE_SIZE[m_type])
		// it is not valid to rotate. There aren't even more arrays for 
		// this tetromino type
*/
const int TetrisGame::Tetromino::SHAPE_SIZE[TetrisGame::Tetromino::END] =
{
	2,	// I
	4,	// J
	4,	// L
	1,	// O
	2,	// S
	4,	// T
	2	// Z
};

TetrisGame::Tetromino::~Tetromino()
{
}

/*
	Rotate the current Tetromino depending on the given "action".
	This Method sets the m_rotation index. 

	Example Usage:
		currentTetromino.rotate(Tetromino::FORWARD);
		// clockwise rotation of current tetromino 
*/
void TetrisGame::Tetromino::rotate(ROTATION_ACTION action)
{
	switch (action) {
	
	case Tetromino::FORWARD: // right rotation => m_rotation + 1
		this->m_rotation = ++m_rotation % SHAPE_SIZE[m_type];
		break;
	
	case Tetromino::BACKWARD: // left rotation => m_rotation - 1
		this->m_rotation = --m_rotation % SHAPE_SIZE[m_type];
		break;
	}

}

/*
	Move the current Tetromino depending on the given "action".
	Options are RIGHT, LEFT, DOWN.
	Only a single action can be perfomed per method-call.

	Example Usage:
		currentTetromino.move(Tetromino::DOWN)
		// Moves the current tetromino one position down. 
		// It increases the Y-coordinate by one.
*/
void TetrisGame::Tetromino::move(MOVE_ACTION action)
{
	switch (action) {
	case RIGHT:
		this->m_position.x++;
		break;
	case LEFT:
		this->m_position.x--;
		break;
	case DOWN:
		this->m_position.y++;
	}
}