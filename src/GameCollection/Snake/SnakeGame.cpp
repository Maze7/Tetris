#include "SnakeGame.h"
#include <iostream>

void SnakeGame::SnakeGame::handleEvent(const sf::Event sfevent)
{
	switch (sfevent.key.code) {
	case sf::Keyboard::W:
		m_snake.changeDirection(Snake::MOVE_UP);
		break;
	case sf::Keyboard::A:
		m_snake.changeDirection(Snake::MOVE_LEFT);
		break;
	case sf::Keyboard::S:
		m_snake.changeDirection(Snake::MOVE_DOWN);
		break;
	case sf::Keyboard::D:
		m_snake.changeDirection(Snake::MOVE_RIGHT);
		break;
	}

	m_isDirectionChanged = true;
}

void SnakeGame::SnakeGame::handleTime()
{
	if (m_clock.getElapsedTime().asMilliseconds() > 100 || m_isDirectionChanged) {
		// Check if snake head is in a valid position
		if (!checkCollision()) {

			// Check if snake head is on top of food
			if (isEatingPossible()) {

				// Eat and generate new food
				m_snake.eat();
				m_field.spawnRandomFood(m_snake);

				// Update score
				m_score.update();
			}

			// Move the snake (automatically travels in the selected current direction)
			m_snake.move();
			m_isDirectionChanged = false;

			// Restart timer
			m_clock.restart();
		}
		else {
			// game over stuff
		}
	}
}

void SnakeGame::SnakeGame::draw(sf::RenderWindow * window, sf::Font * font)
{
	m_field.draw(window, m_snake);
	m_score.draw(window, font);
}

int SnakeGame::SnakeGame::close()
{
	return 0;
}

/*
	Checks if the snake's head collided with the border of the field or with its tail.
	Should be called in the handleTime()-method before the snake.move()-method is called.
*/
bool SnakeGame::SnakeGame::checkCollision()
{
	// Check collision with field borders
	if (m_snake.getSnakeHead().x < 0 || m_snake.getSnakeHead().x > Field::s_ROWS - 1 || m_snake.getSnakeHead().y < 0 || m_snake.getSnakeHead().y > Field::s_COLUMNS) {
		return true;
	}
	
	// Check collision of snake head with its tail
	for (int i = 1; i < m_snake.getSnakeBody()->size(); i++) {
		if (m_snake.getSnakeHead().x == m_snake.getSnakeBody()->at(i).x && m_snake.getSnakeHead().y == m_snake.getSnakeBody()->at(i).y) {
			return true;
		}
	}

	return false;
}

/*
	Checks if the snake's head is on top of the field's food.
	Should be called in the handleTime()-method.

	Example usage:
	if (isEatingPossible()) {
		snake.eat();
		field.spawnRandomFood();
	}
*/
bool SnakeGame::SnakeGame::isEatingPossible()
{ 
	if (m_snake.getSnakeHead().x == m_field.getFood().x && m_snake.getSnakeHead().y == m_field.getFood().y) {
		return true;
	}

	return false;
}
