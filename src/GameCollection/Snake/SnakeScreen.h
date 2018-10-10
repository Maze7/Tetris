#pragma once
#include "../ICollectionScreen.h"
#include "Snake.h"
#include "Field.h"
#include "SnakeScore.h"

namespace SnakeGame 
{
	class SnakeScreen : public GameCollection::ICollectionScreen
	{
	public:
		enum STATES { PLAYING=0, PAUSED=1, GAMEOVER=2 };
	private:
		Snake m_snake;
		Field m_field;
		STATES m_state;
		SnakeScore m_score;
		ICollectionScreen*const* m_nextScreen;
		sf::Clock m_clock;

		bool m_isDirectionChanged;

	public:
		SnakeScreen() : m_nextScreen(nullptr), m_isDirectionChanged(false), m_state(PAUSED) { m_field.spawnRandomFood(m_snake); }
		~SnakeScreen() {}

		void handleEvent(const sf::Event sfevent);
		void handleTime();
		void draw(sf::RenderWindow* window, sf::Font* font);
		int close(ICollectionScreen** screen);
		const STATES& getGameState();
		void setGameState(const STATES& newState);


	private:
		bool checkCollision();
		bool isEatingPossible();

	};
}


