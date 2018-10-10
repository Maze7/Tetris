#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Bird.h"

namespace FlappyBirdGame
{
	class Pipe
	{
	public:

		Pipe(int offsetX);
		~Pipe(){}

		void move(float speed, sf::Time deltaTime);
		bool checkBirdCollision(Bird* bird);
		bool isPassedByBird(Bird* bird);
		bool isOutOfWindow();
		void resetPosition(int offsetX);
		void createRandomGap();

		void draw(sf::RenderWindow* window);


	private:
		std::vector<sf::RectangleShape> m_pipeShapes;
		int m_gapSize;
		bool m_isPassed;
	};
}



