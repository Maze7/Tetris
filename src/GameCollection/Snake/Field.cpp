#include "Field.h"

SnakeGame::Field::Field()
{
	// Set up the background
	m_background.setSize(sf::Vector2f(20 * s_ROWS, 20 * s_COLUMNS));
	m_background.setPosition(s_OFFSET, s_OFFSET);
	m_background.setFillColor(sf::Color(0, 51, 0, 255));
}

/*
	Spawns food for the snake in the field by randomly generating a position for the m_food.
	This position is used later in the draw()-method to create and draw a sf::RectangleShape.

	Example usage:
	if ( // snake head is on food)
		snake.eat();
		field.spawnRandomFood();
*/
void SnakeGame::Field::spawnRandomFood(Snake& snake)
{
	do {
		m_food.x = rand() % (s_ROWS - 1);
		m_food.y = rand() % (s_COLUMNS - 1);
	} while (!isSpaceEmpty(snake));
}

/*
	Checks if the the m_food is not placed in the snake.
	Private helper function for spawnRandomFood().
*/
bool SnakeGame::Field::isSpaceEmpty(Snake& snake)
{
	for (auto const& snakePos : *snake.getSnakeBody()) {
		if (snakePos.x == m_food.x && snakePos.y == m_food.y) {
			return false;
		}
	}

	return true;
}

void SnakeGame::Field::draw(sf::RenderWindow* window, Snake& snake)
{
	// Draw Background
	window->draw(m_background);

	// Draw Food
	sf::RectangleShape block(sf::Vector2f(s_BLOCK_SIZE, s_BLOCK_SIZE));
	block.setOutlineThickness(1.0f);
	block.setOutlineColor(sf::Color(217, 217, 217, 255));
	block.setPosition(20 * m_food.x + s_OFFSET, 20 * m_food.y + s_OFFSET);
	block.setFillColor(sf::Color::Red);
	window->draw(block);

	// Draw Snake
	block.setFillColor(sf::Color::Green);
	block.setOutlineThickness(1.0f);
	block.setOutlineColor(sf::Color(217, 217, 217, 200));
	for (auto& snakePos : *snake.getSnakeBody()) {
		block.setPosition(20 * snakePos.x + s_OFFSET, 20 * snakePos.y + s_OFFSET);
		window->draw(block);
	}
}

