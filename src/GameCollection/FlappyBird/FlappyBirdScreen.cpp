#include "FlappyBirdScreen.h"

FlappyBirdGame::FlappyBirdScreen::FlappyBirdScreen()
{
	// Create pipes
	m_pipes.push_back(Pipe(1400));
	m_pipes.push_back(Pipe(1800));
	m_pipes.push_back(Pipe(2200));
	m_pipes.push_back(Pipe(2600));

	// Create ground
	m_ground.setSize(sf::Vector2f(1200, 40));
	m_ground.setPosition(0, 460);
	m_ground.setFillColor(sf::Color(255, 50, 50, 255));

	// Create background
	m_background.setSize(sf::Vector2f(1200, 500));
	m_background.setPosition(0, 0);
	m_background.setFillColor(sf::Color::Cyan);

	// Create ceiling (so birds can't fly over pipes)
	m_ceiling.setSize(sf::Vector2f(1200, 1));
	m_ceiling.setPosition(0, -20);
	m_ceiling.setFillColor(sf::Color::Transparent);
}

void FlappyBirdGame::FlappyBirdScreen::handleEvent(const sf::Event sfevent)
{
	switch (sfevent.key.code) {
	case sf::Keyboard::W:
		m_bird.flap();
		break;
	}
}

void FlappyBirdGame::FlappyBirdScreen::handleTime()
{
	if (!checkCollision()) {
		sf::Time deltaTime = m_clock.restart(); // clock.restart() returns elapsed time and restarts the timer

		for (auto& pipe : m_pipes) {
			// Move the pipes indepent of frame rate by passing the speed and deltatime to the move function
			pipe.move(200, deltaTime);

			// Check if the bird passed the pipe
			if (pipe.isPassedByBird(&m_bird)) {
				m_score.update();
			}

			// Check if pipe is out of window
			if (pipe.isOutOfWindow()) {
				pipe.resetPosition(1600);
				pipe.createRandomGap();
			}
		}

		// Apply gravitiy to the bird, so it falls down
		m_bird.applyGravity(15.0f, deltaTime);
	}
	else {
		// game over stuff
	}
}

void FlappyBirdGame::FlappyBirdScreen::draw(sf::RenderWindow* window, sf::Font* font)
{
	// Draw background
	window->draw(m_background);

	// Draw bird
	m_bird.draw(window);

	// Draw pipes
	for (auto& pipe : m_pipes) {
		pipe.draw(window);
	}

	// Draw ground and ceiling
	window->draw(m_ground);
	window->draw(m_ceiling);


	// Draw score
	m_score.draw(window, font);
}

int FlappyBirdGame::FlappyBirdScreen::close()
{
	return 0;
}

/*
	Checks if the bird collided with a pipe or the ground.
	Should be called in the handleTime()-method, since positions are updated continiously.
*/
bool FlappyBirdGame::FlappyBirdScreen::checkCollision()
{
	// Check collision with pipe
	for (auto& pipe : m_pipes) {
		if (pipe.checkBirdCollision(&m_bird)) {
			return true;
		}
	}
	
	// Check collision with ground
	if (m_ground.getGlobalBounds().intersects(m_bird.getBirdHitbox().getGlobalBounds())) {
		return true;
	}

	// Check collision with ceiling
	if (m_ceiling.getGlobalBounds().intersects(m_bird.getBirdHitbox().getGlobalBounds())) {
		return true;
	}
	
	return false;
}

void FlappyBirdGame::FlappyBirdScreen::handleCollision()
{
}

