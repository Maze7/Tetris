#include "Game.h"
#include <iostream>

/*
Draws the blocks of the Playfield grid and the tetromino.
Creates sf::RectangleShape's, assigns them the colors saved in the
Playfield's grid / shape colors and sets them to their corresponding position.

Example usage:
window.clear();
playfield.draw(tetromino);
window.diplay();
*/
void TetrisGame::Game::draw(sf::RenderWindow* window)
{
	m_playfield->drawGrid(window);
	m_playfield->drawTetromino(window, m_currentTetromino);
}

/*
	Generates a random tetromino type out of Tetromino::TETROMINO_TYPE and returns it.
*/
TetrisGame::Tetromino::TETROMINO_TYPE TetrisGame::Game::generateRandom()
{
	Tetromino::TETROMINO_TYPE randomTetrominoType = static_cast<Tetromino::TETROMINO_TYPE>(rand() % Tetromino::END);
	return randomTetrominoType;
}


void TetrisGame::Game::handleEvent(const sf::Event sfevent)
{

	if (m_state == GAMEOVER)
		return;
	
	if (!isPosValid()) {
		m_playfield->addTetromino(m_currentTetromino);
		m_currentTetromino = Tetromino(Tetromino::Z, Tetromino::PLAYFIELD_POS);
		return;
	}


	switch (sfevent.key.code) {
	case sf::Keyboard::Space:
		m_currentTetromino.rotate(Tetromino::FORWARD);
		if (!isPosValid())
			m_currentTetromino.rotate(Tetromino::BACKWARD);
		break;
	case sf::Keyboard::A:
		m_currentTetromino.move(Tetromino::LEFT);
		if (!isPosValid())
			m_currentTetromino.move(Tetromino::RIGHT);
		break;
	case sf::Keyboard::D:
		m_currentTetromino.move(Tetromino::RIGHT);
		if (!isPosValid())
			m_currentTetromino.move(Tetromino::LEFT);
		break;
	case sf::Keyboard::S:
		do
			m_currentTetromino.move(Tetromino::DOWN);
		while (isPosValid());
		
		break;
	case sf::Keyboard::P:
		m_state = GAME_STATE::PAUSED;
		break;

	default:
		break;
	}
	
}

bool TetrisGame::Game::isPosValid() 
{
	const sf::Vector2i* pos = &m_currentTetromino.getPosition();
	const Tetromino::TetroShape* currentShape = &TetrisGame::Tetromino::SHAPE_DATA[m_currentTetromino.getType()][m_currentTetromino.getRotation()];

	// other tetrominos
	// iterate the 4x4 tetroshape
	for (uint y = 0; y < 4; y++) {
		for (uint x = 0; x < 4; x++) {

			// if there is something other than zero, there is one part/block of the tetromino 
			if (currentShape[0][y][x] == 1) {
				// this position in the array + the position of the hole tetromino indicates 
				// a valid position in the color-grid of playfield.
				// if there is something other than black, a tetromino color was filled there before
				// => indicates a collision

				if (pos->x + x < 0)
					return false;
				else if (pos->x + x > Playfield::s_COLUMNS - 1)
					return false;
				else if (pos->y + y > Playfield::s_ROWS - 1)
					return false;

				if (m_playfield->getColorOfField(pos->y + y, pos->x + x) != sf::Color::Black)
					return false;
			}
		}
	}

	// return true if no if-condition is true
	return true;
}