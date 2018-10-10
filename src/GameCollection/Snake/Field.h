#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Snake.h"

namespace SnakeGame
{
	class Field
	{

	private:
		// Position of the food that spawns in the field
		sf::Vector2i m_food;

		// Background 
		sf::RectangleShape m_background;

	public: 
		static constexpr int s_ROWS = 25;
		static constexpr int s_COLUMNS = 25;
		static constexpr int s_OFFSET = 10;
		static constexpr int s_BLOCK_SIZE = 20;

	public:
		Field();
		~Field(){}

		sf::Vector2i& getFood() { return m_food; }

		void spawnRandomFood(Snake& snake);
		void draw(sf::RenderWindow* window, Snake& snake);

	private:
		bool isSpaceEmpty(Snake& snake);
	};
} /* namespace SnakeGame */



