#include "Game.h"
#include <string>
#include "TetrisLoader.h"

/*
	Sets the text lables inside the window to the correct
	positions. This method is used to initialize the game. 
	It's advised to call this method inside constructor. Without it
	there will be no text lines. 

	Example usage:
	TetrisGame::Game tetrisGame = TetrisGame::Game();
*/
void TetrisGame::Game::init()
{
	m_levelText.setCharacterSize(32);
	m_scoreText.setCharacterSize(32);
	m_lineCountText.setCharacterSize(32);

	m_levelText.setFillColor(sf::Color::White);
	m_scoreText.setFillColor(sf::Color::White);
	m_lineCountText.setFillColor(sf::Color::White);

	m_levelText.setPosition(500, 400);
	m_scoreText.setPosition(500, 500);
	m_lineCountText.setPosition(500, 600);

	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_levelText.setString("Level: " + std::to_string(m_level));
	m_lineCountText.setString("Lines: " + std::to_string(m_lineCount));	
}

void TetrisGame::Game::handleTime()
{
	if (m_clock.getElapsedTime().asMilliseconds() > m_tickInterval)
	{
		m_currentTetromino.move(Tetromino::DOWN);

		// If the tetromino hit the ground or a block after moving down
		if (!isPosValid())
		{
			// Move it back into a valid position
			m_currentTetromino.move(Tetromino::UP);

			// Handle the game mechanics following the collision
			handleCollision();
		}

		// Start a new tick
		m_clock.restart();
	}
}

/*
	Draw method will be called directly before the next frame will
	displayed. It needs the actual window and font. Both are pointers.
	From here, all other components will be drawn (playfield, tetromino, text, etc).

	Example usage:
	window.clear();
	CollectionEntry.draw(&currentWindow, &currentFont);
	window.diplay();
*/
void TetrisGame::Game::draw(sf::RenderWindow* window, sf::Font* font)
{
	m_playfield.drawGrid(window);
	m_playfield.drawTetromino(window, m_currentTetromino, false);
	m_playfield.drawTetromino(window, m_previewTetromino, false);
	m_playfield.drawTetromino(window, m_collisionPreview, true);

	m_levelText.setFont(*font);
	m_scoreText.setFont(*font);
	m_lineCountText.setFont(*font);

	window->draw(m_scoreText);
	window->draw(m_levelText);
	window->draw(m_lineCountText);
}

int TetrisGame::Game::close()
{
	// todo write highscore and/or do cleanup
	return m_nextScreen;
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
	// Add the tetromino to the grid
	m_playfield.addTetromino(m_currentTetromino);

	// Check for completed rows and delete them
	std::vector<int> completedRows = m_playfield.checkForCompletedRows();

	if (completedRows.size() > 0)
	{
		for (int rowId : completedRows)
		{
			m_playfield.deleteRow(rowId);
		}

		// Update the score system
		updateScoreSystem(completedRows.size());
	}
	

	
	// TODO play delete animation
		
	// Spawn a new tetromino with the shape of the preview
	m_currentTetromino = Tetromino(m_previewTetromino.getType(), Tetromino::PLAYFIELD_POS);
	// Generate a new preview tetromino
	m_previewTetromino = Tetromino(generateRandom(), Tetromino::PREVIEW_POS);
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
	case sf::Keyboard::Up:
	case sf::Keyboard::W:
		m_currentTetromino.rotate(Tetromino::FORWARD);
		if (!isPosValid())
			m_currentTetromino.rotate(Tetromino::BACKWARD);
		break;
	case sf::Keyboard::Left:
	case sf::Keyboard::A:
		m_currentTetromino.move(Tetromino::LEFT);
		if (!isPosValid())
			m_currentTetromino.move(Tetromino::RIGHT);
		break;
	case sf::Keyboard::Right:
	case sf::Keyboard::D:
		m_currentTetromino.move(Tetromino::RIGHT);
		if (!isPosValid())
			m_currentTetromino.move(Tetromino::LEFT);
		break;
	case sf::Keyboard::Down:
	case sf::Keyboard::S:
		m_currentTetromino.move(Tetromino::DOWN);
		m_clock.restart(); // Start a new tick
		break;
	case sf::Keyboard::Space:
		do
			m_currentTetromino.move(Tetromino::DOWN);
		while (isPosValid());

		break;
	case sf::Keyboard::P:
		if (m_state == PAUSED) {
			m_state = GAME_STATE::PAUSED;
		}
		else {
			m_state = PLAYING;
		}
		break;
	case sf::Keyboard::Escape:
		m_state == PAUSED;
		m_running = false;
		m_nextScreen = TetrisGame::TetrisLoader::MENU;
	default:
		break;
	}

	// Update the position of the preview tetromino
	updateCollisionPreview();

	// If the tetromino hit the ground or a block after moving down
	if (!isPosValid())
	{
		// Move it back into a valid position
		m_currentTetromino.move(Tetromino::UP);

		// Handle the game mechanics following the collision
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

				if (m_playfield.getColorOfField(pos->y + y, pos->x + x) != sf::Color::Black)
					return false;
			}
		}
	}

	// return true if no if-condition is true
	return true;
}

const TetrisGame::Game::GAME_STATE& TetrisGame::Game::getGameState()
{
	return m_state;
}

void TetrisGame::Game::setGameState(TetrisGame::Game::GAME_STATE state)
{
	m_state = state;
}

/*
	Updates the score, line count and level depending on rows completed.
	Should be called everytime rows are completed.

	Example usage:
	std::vector<int> completedRows = m_playfield->checkForCompletedRows();
	updateScoreSystem(completedRows.size());

*/
void TetrisGame::Game::updateScoreSystem(uint completedRowCount)
{
	// Update the line count
	m_lineCount += completedRowCount;

	// Increase the score depending on rows completed
	switch (completedRowCount)
	{
	case 1:
		m_score += 40 * m_level;
		break;
	case 2:
		m_score += 100 * m_level;
		break;
	case 3:
		m_score += 300 * m_level;
		break;
	case 4:
		m_score += 1200 * m_level;
		break;
	default:
		break;
	}

	// Update the sf::Text's that are displayed on screen
	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_levelText.setString("Level: " + std::to_string(m_level));
	m_lineCountText.setString("Lines: " + std::to_string(m_lineCount));
}
