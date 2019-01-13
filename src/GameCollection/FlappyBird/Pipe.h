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
	// Contains pipe top and bottom
	std::vector<sf::RectangleShape> m_pipeShapes;

	// Gap between top and bottom part of the pipe
	int m_gapSize;

	// Bool that is set to true, when a bird passes the pipe
	bool m_isPassed;
};

} /* namespace FlappyBirdGame */



