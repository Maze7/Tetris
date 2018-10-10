#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../ICollectionScreen.h"
#include "Bird.h"
#include "Pipe.h"
#include "FlappyBirdScore.h"

namespace FlappyBirdGame
{
	class FlappyBirdScreen : public GameCollection::ICollectionScreen
	{
	public:
		enum STATES { PLAYING = 0, PAUSED = 1, GAMEOVER = 2 };

	private:
		Bird m_bird;
		std::vector<Pipe> m_pipes;

		sf::RectangleShape m_ground;
		sf::RectangleShape m_ceiling;
		sf::RectangleShape m_background;

		FlappyBirdScore m_score;

		sf::Clock m_clock;

	public:
		FlappyBirdScreen();
		~FlappyBirdScreen() {}

		void handleEvent(const sf::Event sfevent);
		void handleTime();
		void draw(sf::RenderWindow* window, sf::Font* font);
		int close();

	private:
		bool checkCollision();
		void handleCollision();
	};
}



