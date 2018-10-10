#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Playfield.h"
#include "Tetromino.h"
#include "TetrisScore.h"
#include "../ICollectionScreen.h"

namespace TetrisGame
{
	class GameScreen : public GameCollection::ICollectionScreen
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
		sf::Music gameMusic;

		int m_nextScreen = -1;
	public:
		GameScreen(TetrisScore& score);
		~GameScreen() {}

		void handleEvent(const sf::Event sfevent);
		void handleTime();
		void draw(sf::RenderWindow* window, sf::Font* font);
		int close(ICollectionScreen** screen);

		void setDifficulty(int difficulty);
		bool isPosValid();
		bool isPosValid(Tetromino* tetromino);
		Tetromino::TETROMINO_TYPE generateRandom();
		void updateCollisionPreview();
		void handleCollision();
		const GAME_STATE& getGameState();
		void setGameState(GAME_STATE state);
		void setSoundVolume(const float& volume);
	};

}
