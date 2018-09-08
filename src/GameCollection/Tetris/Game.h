#pragma once
#include <SFML/Graphics.hpp>
#include "Playfield.h"
#include "Tetromino.h"
#include "../ICollectionEntry.h"

namespace TetrisGame
{
	class Game : public GameCollection::ICollectionEntry
	{
	public:
		enum GAME_STATE { PLAYING = 0, GAMEOVER = 1, PAUSED = 2 };

	private:
		GAME_STATE m_state;
		Tetromino m_currentTetromino;
		Tetromino m_previewTetromino;
		Tetromino m_collisionPreview;
		Playfield * m_playfield;
		
		uint m_level;
		uint m_score;
		uint m_lineCount;
		uint m_tickInterval;

		sf::Clock m_totalTime;
		sf::Clock m_clock;

	public:
		Game() 
			: m_state(Game::PLAYING)
			, m_currentTetromino(generateRandom()
			, Tetromino::PLAYFIELD_POS)
			, m_previewTetromino(generateRandom()
			, Tetromino::PREVIEW_POS)
			, m_collisionPreview(m_currentTetromino)
			, m_level(1)
			, m_score(0)
			, m_lineCount(0)
			, m_tickInterval(500)
		{}
		
		~Game() {}

		void handleTime();
		void draw(sf::RenderWindow* window);
		void handleEvent(const sf::Event sfevent);

		bool isPosValid();
		bool isPosValid(Tetromino* tetromino);
		Tetromino::TETROMINO_TYPE generateRandom();
		void updateCollisionPreview();
		void handleCollision();

		void updateScoreSystem(uint completedRows);
	};

}