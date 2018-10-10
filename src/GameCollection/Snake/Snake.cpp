#include "Snake.h"
#include <iostream>

SnakeGame::Snake::Snake() : m_currentDirection(MOVE_LEFT)
{
	// Add initial parts of the snake
	m_snakeBody.push_back(sf::Vector2i(13, 14));
	m_snakeBody.push_back(sf::Vector2i(14, 14));
	m_snakeBody.push_back(sf::Vector2i(15, 14));
	m_snakeBody.push_back(sf::Vector2i(16, 14));
	m_snakeBody.push_back(sf::Vector2i(17, 14));
}

/*
	Adds an additional body part to the snake by adding a new position to the snakeBody-vector.
	The added position is added behind the last element.

	Example usage:
	if (// snake head is on food)
		snake.eat();
*/
void SnakeGame::Snake::eat()
{
	// Create a new Vector2i to store the new position
	sf::Vector2i newPart(0, 0);
	
	// Placing the new position depends on the current direction of the snake, 
	// e.g if it's moving down, we want the new part to be added above (y - 1) the last element.
	switch (m_currentDirection) {
	case MOVE_LEFT:
		newPart.x = m_snakeBody.at(m_snakeBody.size() - 1).x + 1;
		break;
	case MOVE_RIGHT:
		newPart.x = m_snakeBody.at(m_snakeBody.size() - 1).x - 1;
		break;
	case MOVE_UP:
		newPart.y = m_snakeBody.at(m_snakeBody.size() - 1).x + 1;
		break;
	case MOVE_DOWN:
		newPart.y = m_snakeBody.at(m_snakeBody.size() - 1).x - 1;
		break;
	}

	// Add the new position to the list
	m_snakeBody.push_back(newPart);

}

/*
	Changes the direction the snake moves. 
	This will take effect in the next "tick" of this game's  handleTime()-method.

	Example usage:
	switch (sfevent.key.code) {
		case sf::Keyboard::W:
			snake.changeDirection(Snake::MOVE_UP);
			break;
	}
*/
void SnakeGame::Snake::changeDirection(SNAKE_DIRECTION direction)
{
	// Only allow the change to happen, if it's not the opposite of the current direction
	switch (direction) {
	case MOVE_LEFT:
		if (m_currentDirection != MOVE_RIGHT) {
			m_currentDirection = direction;
		}
		break;
	case MOVE_RIGHT:
		if (m_currentDirection != MOVE_LEFT) {
			m_currentDirection = direction;
		}
		break;
	case MOVE_UP:
		if (m_currentDirection != MOVE_DOWN) {
			m_currentDirection = direction;
		}
		break;
	case MOVE_DOWN:
		if (m_currentDirection != MOVE_UP) {
			m_currentDirection = direction;
		}
		break;
	}
}

/*
	Moves the snake in the current direction.
	Beginning with the last element of the snakeBody-vector and exluding the head,
	every element is moved to the position of the next element. Then the head is moved.

	Example usage:
	if (clock.getElapsedTime().asMilliseconds() > tickInterval) 
		snake.move();
*/
void SnakeGame::Snake::move()
{
	// Iterate over the snakeBody: Begin with last element and exlude head (0-element)
	for (int i = m_snakeBody.size() - 1; i > 0; i--) {

		// Set the positon of the [i]-element to the position of [i-1] (next) element
		m_snakeBody.at(i).x = m_snakeBody.at(i - 1).x;
		m_snakeBody.at(i).y = m_snakeBody.at(i - 1).y;
	}

	// Move the head by changing its position depending on the current direction
	switch (m_currentDirection) {
	case MOVE_LEFT:
		m_snakeBody.at(0).x += -1;
		break;
	case MOVE_RIGHT:
		m_snakeBody.at(0).x += 1;
		break;
	case MOVE_UP:
		m_snakeBody.at(0).y += -1;
		break;
	case MOVE_DOWN:
		m_snakeBody.at(0).y += 1;
		break;
	}
}
