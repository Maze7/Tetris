#pragma once
#include "../ICollectionEntry.h"
#include "Snake.h"
#include "Field.h"
#include "SnakeScore.h"

namespace SnakeGame 
{
	class SnakeGame : public GameCollection::ICollectionEntry
	{
	private:
		Snake m_snake;
		Field m_field;

		SnakeScore m_score;

		sf::Clock m_clock;

		bool m_isDirectionChanged;

	public:
		SnakeGame() : m_isDirectionChanged(false) { m_field.spawnRandomFood(m_snake); }
		~SnakeGame() {}

		void handleEvent(const sf::Event sfevent);
		void handleTime();
		void draw(sf::RenderWindow* window, sf::Font* font);
		int close();

	private:
		bool checkCollision();
		bool isEatingPossible();

	};
}


