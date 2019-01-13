#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../ICollectionScreen.h"
#include "Bird.h"
#include "Pipe.h"
#include "FlappyBirdScore.h"
#include <SFML/Audio.hpp>

namespace FlappyBirdGame {

class FlappyBirdScreen : public GameCollection::ICollectionScreen
{
public:
	enum GAME_STATE { PLAYING = 0, GAMEOVER = 1, PAUSED = 2 };

private:
	GAME_STATE m_state;
	ICollectionScreen*const* m_nextScreen;
		
	// Bird that the player controls
	Bird m_bird;

	// Vector of pipes: These are the obstacles the bird has to pass
	std::vector<Pipe> m_pipes;

	sf::RectangleShape m_ground;
	sf::RectangleShape m_ceiling;
	sf::RectangleShape m_background;

	// Contains current score and highscores
	FlappyBirdScore m_score;

	// sf::Clock (required for smooth movement)
	sf::Clock m_clock;

	// Sound variables
	sf::SoundBuffer soundBufferJump;
	sf::SoundBuffer soundBufferFail;
	sf::Sound failSound;
	sf::Sound jumpSound;

public:
	FlappyBirdScreen();
	~FlappyBirdScreen() {}

	void handleEvent(const sf::Event sfevent);
	void update();
	void draw(sf::RenderWindow* window, sf::Font* font);
	int close(ICollectionScreen** screen);

	const GAME_STATE& getGameState();
	void setGameState(const GAME_STATE& state);

private:
	bool checkCollision();
};

} /* namespace FlappyBirdGame */



