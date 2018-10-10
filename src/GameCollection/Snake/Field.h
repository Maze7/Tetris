#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Snake.h"

namespace SnakeGame
{
	class Field
	{

	private:
		sf::Vector2i m_food;
		sf::RectangleShape m_background;

	public: 
		static constexpr int s_ROWS = 25;
		static constexpr int s_COLUMNS = 25;
		static constexpr int s_OFFSET = 10;

	public:
		Field();
		~Field(){}

		sf::Vector2i& getFood() { return m_food; }

		void spawnRandomFood(Snake& snake);
		void draw(sf::RenderWindow* window, Snake& snake);

	private:
		bool isSpaceEmpty(Snake& snake);
	};
}



