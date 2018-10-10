#include "Bird.h"
#include <iostream>

FlappyBirdGame::Bird::Bird() : m_currentSpeed(-10.0f)
{
	// Create the bird
	m_birdBox.setSize(sf::Vector2f(20, 20));
	m_birdBox.setPosition(250, 250);

	m_birdBox.setFillColor(sf::Color::Yellow);
	m_birdBox.setOutlineThickness(1.0);
	m_birdBox.setOutlineColor(sf::Color::Black);
}

/*
	Changes the bird's current speed, which will make it move upwards in the next applyGravity() 
	Should be called in the handleEvent()-method after the user pressed the corresponding keybind.

	Example usage:
	case sf::Keyboard::W:
		bird.flap();
		break;
*/
void FlappyBirdGame::Bird::flap()
{
	m_currentSpeed = -5.0f;
}

/*
	Moves the bird downwards by the given force and indepent of framerate.
	Should be called in the handleTime()-method.
*/
void FlappyBirdGame::Bird::applyGravity(float force, sf::Time deltaTime)
{
	m_currentSpeed += force * deltaTime.asSeconds();
	m_birdBox.move(0, m_currentSpeed);
}

void FlappyBirdGame::Bird::draw(sf::RenderWindow * window)
{
	window->draw(m_birdBox);
}
