#include "Game.h"
#include <iostream>

void TetrisGame::Game::handleTime()
{
	if (m_clock.getElapsedTime().asMilliseconds() > 500)
	{
		m_currentTetromino.move(Tetromino::DOWN);

		// Handle the game mechanics, if a tetromino hit the ground or a block after moving down
		if (!isPosValid())
		{
			handleCollision();
		}

		// Start a new tick
		m_clock.restart();
	}
}

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
	m_playfield->drawTetromino(window, m_currentTetromino, false);
	m_playfield->drawTetromino(window, m_collisionPreview, true);
}

/*
	Generates a random tetromino type out of Tetromino::TETROMINO_TYPE and returns it.
*/
TetrisGame::Tetromino::TETROMINO_TYPE TetrisGame::Game::generateRandom()
{
	Tetromino::TETROMINO_TYPE randomTetrominoType = static_cast<Tetromino::TETROMINO_TYPE>(rand() % Tetromino::END);
	return randomTetrominoType;
}

/*
	Updates the position of the collisionPreview-Tetromino.
	Has to be called after the player moved the tetromino or a new one spawned.

	Example usage:
	tetromino.move(Tetromino::Right);
	// check if valid
	updateCollisionPreview();
*/
void TetrisGame::Game::updateCollisionPreview()
{
	m_collisionPreview = m_currentTetromino;

	// Move the preview until it collides with the ground or a block
	do
		m_collisionPreview.move(Tetromino::DOWN);
	while (isPosValid(&m_collisionPreview));
	m_collisionPreview.move(Tetromino::UP); // Move tetromino back into a valid position
}

/*
	Handles the game mechanics following a collision of tetromino with the ground or a block.
	Includes adding it to the grid, deleting the completed row, increasing the score and 
	spawns a new tetromino.

	Example usage:
	if (!isPosValid())
		handleCollision();
*/
void TetrisGame::Game::handleCollision()
{
	// Move it back into a valid position
	m_currentTetromino.move(Tetromino::UP);
	// Add the tetromino to the grid
	m_playfield->addTetromino(m_currentTetromino);

	// Check for completed rows and delete them
	std::vector<int> completedRows = m_playfield->checkForCompletedRows();
	for (int i = 0; i < completedRows.size(); i++)
	{
		m_playfield->deleteRow(completedRows[i]);
	}

	// TODO add completedRows.size() to score
	// TODO play delete animation
		
	// Spawn a new tetromino
	m_currentTetromino = Tetromino(generateRandom(), Tetromino::PLAYFIELD_POS);
	// Update the collision preview for the freshly spawned tetromino
	updateCollisionPreview();

	// Start a new tick
	m_clock.restart();
}


void TetrisGame::Game::handleEvent(const sf::Event sfevent)
{

	if (m_state == GAMEOVER)
		return;

	switch (sfevent.key.code) {
	case sf::Keyboard::W:
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
		m_currentTetromino.move(Tetromino::DOWN);
		break;
	case sf::Keyboard::Space:
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

	// Update the position of the preview tetromino
	updateCollisionPreview();

	// Handle the game mechanics, if a tetromino hit the ground or a block after moving down
	if (!isPosValid())
	{
		handleCollision();
	}
}

/*
	Calls the method isPosValid(Tetromino* tetromino with the member variable
	m_currentTetromino. This method is just for clarity and defines the default 
	tetromino if someone want to know if the position is valid.
*/
bool TetrisGame::Game::isPosValid()
{
	return isPosValid(&m_currentTetromino);
}

/*
	Returns a boolean if the position of the given tetromino-pointer
	is valid or not. Invalid means, the tetromino is somewhere where it
	should not be (outside the field or inside an another tetromino => collision).
	If this method returns true, everything is fine. 

	Example Usage: 
		Tetromino currentTetromino = Tetromino(...);
		currentTetromino.move(Tetromino::RIGHT);
		if (game.isPosValid(&tetromino))
			// ok
		else
			currentTetromino.move(Tetromino::LEFT);
			// position invalid! left wall? or something?
*/
bool TetrisGame::Game::isPosValid(Tetromino* tetromino) 
{
	const sf::Vector2i* pos = &tetromino->getPosition();
	const Tetromino::TetroShape* currentShape = &TetrisGame::Tetromino::SHAPE_DATA[tetromino->getType()][tetromino->getRotation()];

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