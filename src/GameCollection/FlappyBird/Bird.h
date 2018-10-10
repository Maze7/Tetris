#pragma once
#include <SFML/Graphics.hpp>

namespace FlappyBirdGame
{
	class Bird
	{
	public:
		Bird();
		~Bird(){}

		void flap();
		void applyGravity(float force, sf::Time deltaTime);
		const sf::RectangleShape& getBirdHitbox() { return m_birdBox; }

		void draw(sf::RenderWindow* window);

	private:
		// sf::RectangleShape that defines the bird
		sf::RectangleShape m_birdBox;

		// Current velocity of the bird (negativ value = bird moves up, positive value = bird moves down)
		float m_currentSpeed;

	};
} /* namespace FlappyBirdGame */



