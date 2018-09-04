#include "Playfield.h"

TetrisGame::Playfield::~Playfield()
{
}

// Adds the tetromino blocks to the Playfield
void TetrisGame::Playfield::addTetromino(TetrisGame::Tetromino& tetromino)
{
	// Get the shape of the tetromino
	const TetroShape* tetroShape = &TetrisGame::Tetromino::SHAPE_DATA[tetromino.getType()][tetromino.getRotation()];
	sf::Vector2i gridPosition;

	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++)
		{
			// If the block is visible (== 1), add the corresponding color to the m_grid
			if (*tetroShape[y][x] == 1)
			{
				gridPosition.x = tetromino.getPosition().x + x;
				gridPosition.y = tetromino.getPosition().y + y;

				m_grid[gridPosition.y][gridPosition.x] = TetrisGame::Tetromino::SHAPE_COLORS[tetromino.getType()];
			}
		}
	}
}

// Checks each row in m_grid for completion
// return: vector containing the indices of completed rows
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

// Moves all rows above the completed row down
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

void TetrisGame::Playfield::draw(TetrisGame::Tetromino& tetromino)
{
	// Draw grid
	for (int y = 0; y < s_ROWS; y++)
	{
		for (int x = 0; x < s_COLUMNS; x++)
		{
			sf::RectangleShape block(sf::Vector2f(m_BLOCK_SIZE, m_BLOCK_SIZE));
			block.setFillColor(m_grid[y][x]);
			block.setPosition(x * m_BLOCK_SIZE + s_OFFSET, y * m_BLOCK_SIZE + s_OFFSET);
			TetrisGame::m_window->draw(block);
		}
	}

	// Draw tetromino
	// Get tetromino shape
	const TetroShape* tetroShape = &TetrisGame::Tetromino::SHAPE_DATA[tetromino.getType()][tetromino.getRotation()];

	// Iterate over the corresponding SHAPE_DATA (sub)array
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			// If a block is visible (== 1), draw it
			if (*tetroShape[y][x] == 1)
			{
				sf::RectangleShape tetroBlock(sf::Vector2f(m_BLOCK_SIZE, m_BLOCK_SIZE));
				tetroBlock.setFillColor(TetrisGame::Tetromino::SHAPE_COLORS[tetromino.getType()]);
				tetroBlock.setPosition((tetromino.getPosition().x * m_BLOCK_SIZE) + (x * m_BLOCK_SIZE) + s_OFFSET, (tetromino.getPosition().y * m_BLOCK_SIZE) + (y * m_BLOCK_SIZE) + s_OFFSET);
				TetrisGame::m_window->draw(tetroBlock);
			}
		}
	}
}
