#include "Playfield.h"

namespace TetrisGame {
Playfield::~Playfield()
{
}

/*
	Saves the colors of the tetromino blocks in the Playfield's grid 
	at their respective position. This function has to be called after 
	an active tetromino collides after a MOVE::ACTION::DOWN and therefore
	becomes inactive.

	Example usage: 
	if ( // tetromino collided after moving down )
		addTetromino(activeTetromino);
*/
void Playfield::addTetromino(Tetromino& tetromino)
{
	// Get the shape of the tetromino
	const Tetromino::TetroShape* tetroShape = &Tetromino::SHAPE_DATA[tetromino.getType()][tetromino.getRotation()];
	sf::Vector2i gridPosition;

	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++)
		{
			// If the block is visible (== 1), add the corresponding color to the m_grid
			if (tetroShape[0][y][x] == 1)
			{
				gridPosition.x = tetromino.getPosition().x + x;
				gridPosition.y = tetromino.getPosition().y + y;

				m_grid[gridPosition.y][gridPosition.x] = Tetromino::SHAPE_COLORS[tetromino.getType()];
			}
		}
	}
}

/*
	Checks the Playfield's grid for completed rows and returns the indices of the 
	completed rows. A row is completed, if it has no more black (empty) blocks.

	Example usage:
	if ( // tetromino collided after moving down )
		std::vector<int> completedRows = playfield.checkForCompletedRows();
		// remove the completed rows
*/
std::vector<int> Playfield::checkForCompletedRows()
{
	std::vector<int> completedRowsIndices;
	bool completed = true;

	// Iterate over the grid
	for (int y = 0; y < s_ROWS; y++)
	{
		for (int x = 0; x < s_COLUMNS; x++)
		{
			// If a row contains a black block, it's not completed
			if (m_grid[y][x] == sf::Color::Black)
			{
				completed = false;
			}
		}

		if (completed)
		{
			completedRowsIndices.push_back(y);
		}

		completed = true;
	}

	return completedRowsIndices;
}

/*
	Deletes the given row by moving all rows above down, which is achieved by changing 
	the color of a block to the color of the block above it.

	Example usage:
	for (int rowIndex : completedRowsIndices)
		playfield.deleteRow(rowIndex);
*/
void Playfield::deleteRow(unsigned int row)
{
	// Start at the completed row and move one row up every iteration (decrease y-index)
	for (int y = row; y > 0; y--)
	{
		for (int x = 0; x < s_COLUMNS; x++)
		{
			// Set current block color to the color of the block above it
			m_grid[y][x] = m_grid[y - 1][x];
		}
	}
}

sf::Color Playfield::getColorOfField(unsigned int y, unsigned int x)
{
	return m_grid[y][x];
}

/*
	Draws the Playfield's grid => m_grid to m_window
*/
void Playfield::drawGrid(sf::RenderWindow* window)
{
	const unsigned int WIDTH = window->getSize().x;
	const unsigned int HEIGHT = window->getSize().y;
	const unsigned int BLOCK_SIZE{ (HEIGHT - 2 * s_OFFSET) / s_ROWS };

	// build ""Fancy"" grid which shows the end of the playfield
	sf::RectangleShape grid(sf::Vector2f(BLOCK_SIZE * s_COLUMNS, HEIGHT - 2 * s_OFFSET));
	grid.setOutlineColor(sf::Color::White);
	grid.setOutlineThickness(3);
	grid.setFillColor(sf::Color::Black);
	grid.setPosition(s_OFFSET, s_OFFSET);
	window->draw(grid);

	// Create a sf::Rectangleshape to draw the blocks in the playfield
	sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
	block.setOutlineColor(sf::Color::Black);
	block.setOutlineThickness(1);

	// Draw color  grid
	for (int y = 0; y < s_ROWS; y++)
	{
		for (int x = 0; x < s_COLUMNS; x++)
		{
			if (m_grid[y][x] != sf::Color::Black) {
				// Create the blocks as sf::RectangleShape's and assign color and position
				block.setFillColor(m_grid[y][x]);
				block.setPosition(x * BLOCK_SIZE + s_OFFSET, y * BLOCK_SIZE + s_OFFSET);

				// Call draw-function of window
				window->draw(block);
			}
		}
	}
}

/*
	Draws the given tetromino into the current playfield. 
	Params: @window - sf::Window* on which the tetromino @tetro
			should displayed. In case @transparency is true, the
			given @tetro wont have a color and only the outline will
			visible.
	Example Usage:
		Playfield field(..);
		Playfield field2(..);
		Tetromino tetro(..);
		field.drawTetromino(&window, tetro, true);
		field2.drawTetromino(&window, tetro, true);
		// now both fields contains a visible tetromino
		// in this specific case, the playfield should contain other offsets
		// so they will be drawn alongsite eachother
*/
void Playfield::drawTetromino(sf::RenderWindow* window, Tetromino & tetromino, bool transparency) {

	const unsigned int HEIGHT = window->getSize().y;
	const unsigned int BLOCK_SIZE{ (HEIGHT - 2 * s_OFFSET) / s_ROWS };

	// Draw tetromino
	// Get tetromino shape
	const Tetromino::TetroShape* tetroShape = &Tetromino::SHAPE_DATA[tetromino.getType()][tetromino.getRotation()];
	sf::Vector2i tetrominoBlockPosition;

	// Create a sf::RectangleShape to draw the blocks
	sf::RectangleShape tetroBlock(sf::Vector2f(38, 38));

	// Assign the respective color to the shape
	if (transparency) {
		tetroBlock.setFillColor(sf::Color::Transparent);
		tetroBlock.setOutlineColor(sf::Color::White);
		tetroBlock.setOutlineThickness(1);
	} else {
		tetroBlock.setFillColor(Tetromino::SHAPE_COLORS[tetromino.getType()]);
	}

	// Iterate over the corresponding SHAPE_DATA (sub)array
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			// If a block is visible (== 1), draw it
			if (tetroShape[0][y][x] == 1) {
				// Calculate the on-screen position of the block
				tetrominoBlockPosition.x = (tetromino.getPosition().x + x) * BLOCK_SIZE + s_OFFSET;
				tetrominoBlockPosition.y = (tetromino.getPosition().y + y) * BLOCK_SIZE + s_OFFSET;

				// Set the position of the block
				tetroBlock.setPosition(tetrominoBlockPosition.x, tetrominoBlockPosition.y);

				// Call draw-function of window
				window->draw(tetroBlock);
			}
		}
	}
}

/*
	Changes the color of the completed rows.

	Example usage:
	m_completedRows = m_playfield.checkForCompletedRows();
	if (m_completedRows.size() > 0)
		m_playfield.markCompletedRows(&m_completedRows, sf::Color::White);
*/
void Playfield::markCompletedRows(std::vector<int>* completedRows, sf::Color color)
{
	for (int& rowId : *completedRows) {
		for (int x = 0; x < s_COLUMNS; x++) {
			m_grid[rowId][x] = color;
		}
	}
}

/*
	Clears the whole Playfield.
	Currently unused.
*/
void Playfield::resetPlayfield()
{
	for (int y = 0; y < s_ROWS; y++) {
		for (int x = 0; x < s_COLUMNS; x++)	{
			m_grid[y][x] = sf::Color::Black;
		}
	}
}
} /* namespace TetrisGame */