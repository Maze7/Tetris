#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

namespace SnakeGame {
class Snake	{
public: 
	enum SNAKE_DIRECTION { MOVE_LEFT = 0, MOVE_RIGHT = 1, MOVE_UP = 2, MOVE_DOWN = 3 };

private:
	// The snakebody is stored as a Vector of positions - The actual screen position will be calculated in the Field's draw()-method
	std::vector<sf::Vector2i> m_snakeBody;

	// Current direction of the snake's head
	SNAKE_DIRECTION m_currentDirection;

public:
	Snake();
	~Snake() {}

	sf::Vector2i& getSnakeHead() { return m_snakeBody.at(0); }
	std::vector<sf::Vector2i>* getSnakeBody() { return &m_snakeBody; }

	void eat();
	void changeDirection(SNAKE_DIRECTION direction);
	void move();
};

} /* namespace SnakeGame */



