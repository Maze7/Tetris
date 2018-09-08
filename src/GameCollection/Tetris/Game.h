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
		TetrisGame::Tetromino m_currentTetromino;
		TetrisGame::Tetromino m_previewTetromino;
		Playfield* m_playfield;
		int m_level;
		sf::Clock m_clock;

	public:
		Game() : m_state(Game::PLAYING), m_currentTetromino(generateRandom(), TetrisGame::Tetromino::PLAYFIELD_POS), m_previewTetromino(generateRandom(), TetrisGame::Tetromino::PREVIEW_POS) {}
		~Game() {}

		void handleTime() {};
		void draw(sf::RenderWindow* window);
		void handleEvent(const sf::Event sfevent);

		bool isPosValid();
		Tetromino::TETROMINO_TYPE generateRandom();
	};

}