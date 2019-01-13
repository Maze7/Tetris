#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Playfield.h"
#include "Tetromino.h"
#include "TetrisScore.h"
#include "../ICollectionScreen.h"

namespace TetrisGame {

class GameScreen : public GameCollection::ICollectionScreen
{
public:
	enum GAME_STATE { PLAYING = 0, GAMEOVER = 1, PAUSED = 2 };

private:
	/*
	Discribes the current GAME_STATE. 
	PLAYING		= Game is running. This doesnt mean this game is actual focused or the use 
					is currently playing.
	GAMEOVER	= Game is Gameover. Nearly every gamelogic would skipped. RETURN is allowed. 
	PAUSED		= Game is Paused. Used to pause music.
	Default is playing
	=> Cant be empty (nullptr, null, zero)
	*/
	GAME_STATE m_state;
		
	/*
	Tetromino which is placed on the Playfield.
	=> Cant be empty (nullptr, null, zero)
	*/
	Tetromino m_currentTetromino;

	/*
	Tetromino which is shown in the right box. 
	After m_currentTetromino gets a collision, it will set
	to m_previewTetromino
	=> Cant be empty (nullptr, null, zero)
	*/
	Tetromino m_previewTetromino;

	/*
	This Tetromino is a copy of m_currentTetromino and 
	show where the m_currentTetromino would collision with ground/other tetromino
	=> Cant be empty (nullptr, null, zero)
	*/
	Tetromino m_collisionPreview;

	Playfield m_playfield;
	TetrisScore& m_score;

	/*
	sf::Clock is counting ms. 
	Presents the actual game ticks.
	*/
	sf::Clock m_clock;
	unsigned int m_tickInterval;
	std::vector<int> m_completedRows;
	sf::Music gameMusic;

	/*
	m_nextScreen is an identifier for the next screen which will displayed.
	It is one entry out of TetrisLoader::s_modulScreens
	*/
	int m_nextScreen = -1;

public:
	GameScreen(TetrisScore& score);
	~GameScreen() {}

	void handleEvent(const sf::Event sfevent);
	void update();
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

} /* namespace TetrisGame */
