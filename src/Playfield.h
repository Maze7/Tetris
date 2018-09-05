#pragma once
#include <SFML/Graphics.hpp>
#include "TetrisWindow.h"
#include "Tetromino.h"

namespace TetrisGame 
{

	class Playfield
	{
	public:
		static constexpr int s_ROWS = 22;
		static constexpr int s_COLUMNS = 10;
		static constexpr int s_OFFSET = 10;

		const uint m_WIDTH{ TetrisGame::getSFWindow()->getSize().x };
		const uint m_HEIGHT{ TetrisGame::getSFWindow()->getSize().y };

	private:

		std::vector<std::vector<sf::Color>> m_grid;
		uint m_BLOCK_SIZE{ (m_HEIGHT - 2 * s_OFFSET) / s_COLUMNS };

	public:
		Playfield() : m_grid(s_ROWS, std::vector<sf::Color>(s_COLUMNS, sf::Color::Black)) {};
		~Playfield();
		void addTetromino(TetrisGame::Tetromino& tetromino);
		std::vector<int> checkForCompletedRows();
		void deleteRow(uint row);
		void draw(TetrisGame::Tetromino& tetromino);

	private:
		void drawGrid();
		void drawTetromino(TetrisGame::Tetromino& tetromino);

	};
}
