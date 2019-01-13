#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"

namespace TetrisGame {

class Playfield {

private:
	std::vector<std::vector<sf::Color>> m_grid;

public:
	static constexpr int s_ROWS = 20;
	static constexpr int s_COLUMNS = 10;
	static constexpr int s_OFFSET = 10;

public:
	Playfield() : m_grid(s_ROWS, std::vector<sf::Color>(s_COLUMNS, sf::Color::Black)) {};

	~Playfield();
	void addTetromino(TetrisGame::Tetromino& tetromino);
	std::vector<int> checkForCompletedRows();
	void deleteRow(unsigned int row);
	sf::Color getColorOfField(unsigned int y, unsigned int x);

	void drawGrid(sf::RenderWindow* window);
	void drawTetromino(sf::RenderWindow* window, TetrisGame::Tetromino& tetromino, bool transparency);

	void markCompletedRows(std::vector<int>* completedRows, sf::Color color);
	void resetPlayfield();
};

} /* namespace TetrisGame */
