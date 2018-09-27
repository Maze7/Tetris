#pragma once
#include <SFML\Graphics.hpp>

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
		sf::RectangleShape m_birdBox;
		float m_currentSpeed;

	};
}



