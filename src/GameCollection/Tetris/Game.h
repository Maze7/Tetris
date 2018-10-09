#pragma once
#include <SFML/Graphics.hpp>
#include "Playfield.h"
#include "Tetromino.h"
#include "TetrisScore.h"
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
		Playfield m_playfield;

		TetrisScore& m_score;
		sf::Clock m_clock;
		uint m_tickInterval;
		std::vector<int> m_completedRows;

		int m_nextScreen = -1;
	public:
		Game(TetrisScore& score);
		~Game() {}

		void handleEvent(const sf::Event sfevent);
		void handleTime();
		void draw(sf::RenderWindow* window, sf::Font* font);
		int close(ICollectionEntry** screen);

		void setDifficulty(int difficulty);
		bool isPosValid();
		bool isPosValid(Tetromino* tetromino);
		Tetromino::TETROMINO_TYPE generateRandom();
		void updateCollisionPreview();
		void handleCollision();
		const GAME_STATE& getGameState();
		void setGameState(GAME_STATE state);
	};

}
