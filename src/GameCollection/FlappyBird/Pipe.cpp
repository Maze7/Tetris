#include "Pipe.h"
#include <iostream>

FlappyBirdGame::Pipe::Pipe(int offsetX) : m_gapSize(100), m_isPassed(false)
{
	// Add the RectangleShapes, that make up the pipe
	m_pipeShapes.push_back(sf::RectangleShape());
	m_pipeShapes.push_back(sf::RectangleShape());

	// Create the pipe
	for (auto& pipe : m_pipeShapes) {
		pipe.setPosition(offsetX, 0);
		pipe.setFillColor(sf::Color::Green);
		pipe.setOutlineThickness(1.0f);
		pipe.setOutlineColor(sf::Color::Black);
	}

	// Create a gap in the pipe at a random position
	createRandomGap();
}

/*
	Moves the pipe to the left, creating the effect of a camera/bird moving to the right.
	Should be called in the handleTime()-method.
*/
void FlappyBirdGame::Pipe::move(float speed, sf::Time deltaTime)
{
	for (auto& pipe : m_pipeShapes) {
		pipe.move(speed * -deltaTime.asSeconds(), 0);
	}
}

/*
	Checks if a bird collided with the pipe.
	Should be called in the handleTime()-method.
*/
bool FlappyBirdGame::Pipe::checkBirdCollision(Bird* bird)
{
	bool is_collided = false;

	for (auto& pipe : m_pipeShapes) {
		if (pipe.getGlobalBounds().intersects(bird->getBirdHitbox().getGlobalBounds())) {
			is_collided = true;
		}
	}

	return is_collided;
}

/*
	Checks if a bird passed the pipe.
	Only returns true, if pipe has not been passed yet.
	Should be called in the handleTime()-method.

	Example usage:
	if (pipe.isPassedByBird(&bird)) {
		// Increase score
	}
*/
bool FlappyBirdGame::Pipe::isPassedByBird(Bird * bird)
{
	// If pipe has not been passed yet
	if (!m_isPassed) {
		// If right end of the pipe is behind the left end of the bird
		if (m_pipeShapes.at(0).getPosition().x + m_pipeShapes.at(0).getSize().x < bird->getBirdHitbox().getPosition().x) {
			m_isPassed = true;
			return true;
		}
	}
	return false;
}

/*
	Checks if the pipe is out of the window, meaning it's no longer displayed on the screen,
	requiring a reset of position.
	Should be called in the handleTime()-method.

	Example usage:
	if (pipe.isOutOfWindow()) {
		pipe.resetPosition(offsetX);
		pipe.createRandomGap();
	}
*/
bool FlappyBirdGame::Pipe::isOutOfWindow()
{
	return m_pipeShapes.at(0).getPosition().x + m_pipeShapes.at(0).getSize().x < 0;
}

/*
	Resets the position of the pipe to the given position.

	Example usage: 
	if (pipe.isOutOfWindow()) {
		pipe.resetPosition(offsetX);
		pipe.createRandomGap();
	}
*/
void FlappyBirdGame::Pipe::resetPosition(int offsetX)
{
	for (auto& pipe : m_pipeShapes) {
		pipe.setPosition(offsetX, 0);
	}

	m_isPassed = false;
}

/*
	Creates a random gap in the pipe.
	Should be called in the constructor of this class and after a resetting the position.

	Example usage:
	if (pipe.isOutOfWindow()) {
		pipe.resetPosition(offsetX);
		pipe.createRandomGap();
	}
*/
void FlappyBirdGame::Pipe::createRandomGap()
{
	int sizeTop = rand() % (300 - 100 + 1) + 100;
	int sizeBottom = 500 - sizeTop - m_gapSize;

	m_pipeShapes.at(0).setSize(sf::Vector2f(40, sizeTop));
	m_pipeShapes.at(1).setSize(sf::Vector2f(40, sizeBottom));
	m_pipeShapes.at(1).move(0, sizeTop + m_gapSize);
}

void FlappyBirdGame::Pipe::draw(sf::RenderWindow* window)
{
	for (auto& pipe : m_pipeShapes) {
		window->draw(pipe);
	}
}
