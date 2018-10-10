#pragma once
#include <SFML/Graphics.hpp>
#include "../ICollectionScreen.h"
#include "SnakeScore.h"

namespace SnakeGame {

class SnakeScoreScreen : public GameCollection::ICollectionScreen {
private:
	SnakeScore& m_score;
	sf::Texture m_background;

public:
	SnakeScoreScreen(SnakeScore& score);
	virtual ~SnakeScoreScreen() {};

	void handleEvent(const sf::Event sfevent);
	void draw(sf::RenderWindow* window, sf::Font* font);
	int close(ICollectionScreen** screen);
};

} /* namespace SnakeGame */
