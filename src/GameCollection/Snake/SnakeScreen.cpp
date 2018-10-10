#include "SnakeScreen.h"
#include "../Collection.h"
#include "SnakeLoader.h"

#include <iostream>

SnakeGame::SnakeScreen::SnakeScreen() :
		m_nextScreen(nullptr),
		m_isDirectionChanged(false),
		m_state(PAUSED) {
	m_field.spawnRandomFood(m_snake);
	soundBuffer.loadFromFile("static/snake_eat.wav");
	eatSound.setBuffer(soundBuffer);
	eatSound.setLoop(false);
}

void SnakeGame::SnakeScreen::handleEvent(const sf::Event sfevent)
{
	if (m_state == GAMEOVER) {
		if (sfevent.key.code == sf::Keyboard::Return) {
			m_running = false;
			m_nextScreen = &GameCollection::Collection::getEntrys()->at(SnakeLoader::MODUL_NAME);
		} else {
			return;
		}
	}
	switch (sfevent.key.code) {
	case sf::Keyboard::W:
		m_snake.changeDirection(Snake::MOVE_UP);
		break;
	case sf::Keyboard::A:
		m_snake.changeDirection(Snake::MOVE_LEFT);
		break;
	case sf::Keyboard::S:
		m_snake.changeDirection(Snake::MOVE_DOWN);
		break;
	case sf::Keyboard::D:
		m_snake.changeDirection(Snake::MOVE_RIGHT);
		break;
	case sf::Keyboard::Escape:
		m_running=false;
		m_nextScreen = &GameCollection::Collection::getEntrys()->at(SnakeLoader::MODUL_NAME);
		break;
	}

	m_isDirectionChanged = true; // makes the snake move immediately in the handleTime()-method
}

void SnakeGame::SnakeScreen::handleTime()
{
	if (m_state == GAMEOVER) {
		return; // no gameticks if gameover
	}
	// If time for a new tick or player changed direction
	if (m_clock.getElapsedTime().asMilliseconds() > 100 || m_isDirectionChanged) {

		// Check if snake head is in a valid position
		if (!checkCollision()) {

			// Check if snake head is on top of food
			if (isEatingPossible()) {

				// Eat and generate new food
				m_snake.eat();
				eatSound.play();
				m_field.spawnRandomFood(m_snake);

				// Update score
				m_score.update();
			}

			// Move the snake (automatically travels in the selected current direction)
			m_snake.move();
			m_isDirectionChanged = false;

			// Restart timer
			m_clock.restart();
		}
		else {
			m_state = GAMEOVER;
		}
	}
}

void SnakeGame::SnakeScreen::draw(sf::RenderWindow * window, sf::Font * font)
{
	m_field.draw(window, m_snake);
	m_score.draw(window, font);
	if (m_state == GAMEOVER) {
		//const uint BLOCK_SIZE{ (window->getSize().y- 2 * m_field.s_OFFSET) / m_field.s_ROWS };
		sf::Vector2f size(m_field.s_BLOCK_SIZE * m_field.s_COLUMNS, window->getSize().y - 2 * m_field.s_OFFSET);

		sf::RectangleShape shape;
		shape.setSize(size);
		shape.setPosition(m_field.s_OFFSET, m_field.s_OFFSET);
		shape.setFillColor(sf::Color(255, 150, 150, 150));
		window->draw(shape);

		sf::Text gameoverText("\t \t \t  GameOver! \n      \t Press <RETURN>", *font, 50);
		gameoverText.setPosition(50.f, 250.f);
		window->draw(gameoverText);
	}
}

int SnakeGame::SnakeScreen::close(ICollectionScreen** screen)
{
	*screen = *m_nextScreen;
	return CONTINUE;
}

/*
	Checks if the snake's head collided with the border of the field or with its tail.
	Should be called in the handleTime()-method before the snake.move()-method is called.
*/
bool SnakeGame::SnakeScreen::checkCollision()
{
	// Check collision with field borders
	if (m_snake.getSnakeHead().x < 0 || m_snake.getSnakeHead().x > Field::s_ROWS - 1 || m_snake.getSnakeHead().y < 0 || m_snake.getSnakeHead().y > Field::s_COLUMNS - 1) {
		return true;
	}
	
	// Check collision of snake head with its tail (Start at 1, because head is at index 0)
	for (int i = 1; i < m_snake.getSnakeBody()->size(); i++) {
		if (m_snake.getSnakeHead().x == m_snake.getSnakeBody()->at(i).x && m_snake.getSnakeHead().y == m_snake.getSnakeBody()->at(i).y) {
			return true;
		}
	}

	return false;
}

/*
	Checks if the snake's head is on top of the field's food.
	Should be called in the handleTime()-method.

	Example usage:
	if (isEatingPossible()) {
		snake.eat();
		field.spawnRandomFood();
	}
*/
bool SnakeGame::SnakeScreen::isEatingPossible()
{ 
	if (m_snake.getSnakeHead().x == m_field.getFood().x && m_snake.getSnakeHead().y == m_field.getFood().y) {
		return true;
	}

	return false;
}

const SnakeGame::SnakeScreen::STATES& SnakeGame::SnakeScreen::getGameState() {
	return m_state;
}

void SnakeGame::SnakeScreen::setGameState(const STATES& newState) {
	m_state = newState;
}
