#include "Playfield.h"

TetrisGame::Playfield::~Playfield()
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
void TetrisGame::Playfield::addTetromino(TetrisGame::Tetromino& tetromino)
{
	// Get the shape of the tetromino
	const TetrisGame::Tetromino::TetroShape* tetroShape = &TetrisGame::Tetromino::SHAPE_DATA[tetromino.getType()][tetromino.getRotation()];
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

				m_grid[gridPosition.y][gridPosition.x] = TetrisGame::Tetromino::SHAPE_COLORS[tetromino.getType()];
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
std::vector<int> TetrisGame::Playfield::checkForCompletedRows()
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
void TetrisGame::Playfield::deleteRow(uint row)
{
	// Start at the completed row and move one row up every iteration (decrease y-index)
	for (int y = row; y > 0; y--)
	{
		for (int x = 0; s_COLUMNS; x++)
		{
			// Set current block color to the color of the block above it
			m_grid[y][x] = m_grid[y - 1][x];
		}
	}
}

sf::Color TetrisGame::Playfield::getColorOfField(uint y, uint x)
{
	return m_grid[y][x];
}

/*
	Draws the Playfield's grid => m_grid to m_window
*/
void TetrisGame::Playfield::drawGrid(sf::RenderWindow* window)
{
	// build ""Fancy"" grid which shows the end of the playfield
	sf::RectangleShape grid(sf::Vector2f(m_BLOCK_SIZE * s_COLUMNS, m_HEIGHT - 2 * s_OFFSET));
	grid.setOutlineColor(sf::Color::White);
	grid.setOutlineThickness(3);
	grid.setFillColor(sf::Color::Black);
	grid.setPosition(s_OFFSET, s_OFFSET);
	window->draw(grid);

	// Draw color  grid
	for (int y = 0; y < s_ROWS; y++)
	{
		for (int x = 0; x < s_COLUMNS; x++)
		{
			if (m_grid[y][x] != sf::Color::Black) {
				// Create the blocks as sf::RectangleShape's and assign color and position
				sf::RectangleShape block(sf::Vector2f(m_BLOCK_SIZE, m_BLOCK_SIZE));
				block.setFillColor(m_grid[y][x]);
				block.setPosition(x * m_BLOCK_SIZE + s_OFFSET, y * m_BLOCK_SIZE + s_OFFSET);

				// Call draw-function of window
				window->draw(block);
			}
		}
	}
}

/*
	Draws the given tetromino into the current playfield. 
	Example Usage:
		Playfield field(..);
		Playfield field2(..);
		Tetromino tetro(..);
		field.drawTetromino(tetro);
		field2.drawTetromino(tetro);
		// now both fields contains a visible tetromino
		// in this specific case, the playfield should contain other offsets
		// so they will be drawn alongsite eachother
*/
void TetrisGame::Playfield::drawTetromino(sf::RenderWindow* window, TetrisGame::Tetromino & tetromino, bool transparency)
{
	// Draw tetromino
	// Get tetromino shape
	const TetrisGame::Tetromino::TetroShape* tetroShape = &TetrisGame::Tetromino::SHAPE_DATA[tetromino.getType()][tetromino.getRotation()];
	sf::Vector2i tetrominoBlockPosition;

	// Iterate over the corresponding SHAPE_DATA (sub)array
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			// If a block is visible (== 1), draw it
			if (tetroShape[0][y][x] == 1)
			{
				// Create the blocks as sf::RectangleShape'
				sf::RectangleShape tetroBlock(sf::Vector2f(38, 38));

				// Assign the respective color to the shape
				if (transparency) {
					tetroBlock.setFillColor(sf::Color::Transparent);
					tetroBlock.setOutlineColor(sf::Color::White);
					tetroBlock.setOutlineThickness(1);
				} 
				else {
					tetroBlock.setFillColor(TetrisGame::Tetromino::SHAPE_COLORS[tetromino.getType()]);
				}

				// Calculate the on-screen position of the block
				tetrominoBlockPosition.x = (tetromino.getPosition().x + x) * m_BLOCK_SIZE + s_OFFSET;
				tetrominoBlockPosition.y = (tetromino.getPosition().y + y) * m_BLOCK_SIZE + s_OFFSET;

				// Set the position of the block
				tetroBlock.setPosition(tetrominoBlockPosition.x, tetrominoBlockPosition.y);

				// Call draw-function of window
				window->draw(tetroBlock);
			}
		}
	}
}
