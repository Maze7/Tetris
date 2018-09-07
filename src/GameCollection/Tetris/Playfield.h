#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"

namespace TetrisGame 
{

	class Playfield
	{
	public:
		static constexpr int s_ROWS = 20;
		static constexpr int s_COLUMNS = 10;
		static constexpr int s_OFFSET = 10;

		uint m_WIDTH;
		uint m_HEIGHT;

	private:

		std::vector<std::vector<sf::Color>> m_grid;
		uint m_BLOCK_SIZE{ (m_HEIGHT - 2 * s_OFFSET) / s_ROWS };
		sf::RenderWindow* const m_window;

	public:
		Playfield(sf::RenderWindow* window) : m_grid(s_ROWS, std::vector<sf::Color>(s_COLUMNS, sf::Color::Black)), m_WIDTH(window->getSize().x), m_HEIGHT(window->getSize().y), m_window(window) {};
		~Playfield();
		void addTetromino(TetrisGame::Tetromino& tetromino);
		std::vector<int> checkForCompletedRows();
		void deleteRow(uint row);

		void drawGrid();
		void drawTetromino(TetrisGame::Tetromino& tetromino);

	};
}
