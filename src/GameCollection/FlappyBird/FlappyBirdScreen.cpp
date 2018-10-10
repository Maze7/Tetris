#include "FlappyBirdScreen.h"

FlappyBirdGame::FlappyBirdScreen::FlappyBirdScreen() : m_state(PLAYING) {
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

	if (!soundBufferJump.loadFromFile("static/flappy_jump.wav")) {
		std::cout << "flappy_jump.wav could not found \n";
	} else {
		jumpSound.setBuffer(soundBufferJump);
		jumpSound.setLoop(false);
	}
	if (!soundBufferFail.loadFromFile("static/flappy_fail.wav")) {
		std::cerr << "flappy_fail.wav could not found \n";
	} else {
		failSound.setBuffer(soundBufferFail);
		failSound.setLoop(false);
	}

}

void FlappyBirdGame::FlappyBirdScreen::handleEvent(const sf::Event sfevent)
{
	switch (sfevent.key.code) {
	case sf::Keyboard::Up:
	case sf::Keyboard::W:
		m_bird.flap();
		jumpSound.play();
		break;
	}
}

void FlappyBirdGame::FlappyBirdScreen::handleTime() {

	if (m_state == GAMEOVER) {
		return;
	}
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
		// Gameover
		m_state = GAMEOVER;
		failSound.play();
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

	// Draw gameover screen
	if (m_state == GAMEOVER) {
		sf::Vector2f size(1200, 500);
		sf::RectangleShape shape;
		shape.setSize(size);
		shape.setFillColor(sf::Color(255, 150, 150, 150));
		window->draw(shape);
		sf::Text gameoverText("\t \t \t  GameOver! \n      \t Press <RETURN>", *font, 50);
		gameoverText.setPosition(50.f, 250.f);
		window->draw(gameoverText);
	}
}

int FlappyBirdGame::FlappyBirdScreen::close()
{
	return 0;
}

/*
	Returns the game state.
*/
const FlappyBirdGame::FlappyBirdScreen::GAME_STATE& FlappyBirdGame::FlappyBirdScreen::getGameState()
{
	return m_state;
}

/*
	Sets the game state.
*/
void FlappyBirdGame::FlappyBirdScreen::setGameState(const GAME_STATE& state)
{
	m_state = state;
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

