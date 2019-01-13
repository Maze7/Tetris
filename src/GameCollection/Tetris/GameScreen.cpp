#include <string>

#include "GameScreen.h"
#include "TetrisLoader.h"

namespace TetrisGame {
/*
	Creates an Object of GameScreen. It contains the main tetris game logic.
	It will create its own Playfield and and handle everything which is needed. 
	It inherits from ICollectionScreen and can loaded into Collection::run
	Param:
		TetrisScore& - a reference to TetrisScore. 
						Be aware: each time an instance of TetrisScore is created, 
						there is one read operation from local disk
						
*/
GameScreen::GameScreen(TetrisScore& score)
			: m_state(GameScreen::PAUSED)
			, m_currentTetromino(generateRandom(), Tetromino::PLAYFIELD_POS)
			, m_previewTetromino(generateRandom(), Tetromino::PREVIEW_POS)
			, m_collisionPreview(m_currentTetromino)
			, m_tickInterval(500)
			, m_playfield(Playfield())
			, m_score(score) {

	// start music
	gameMusic.openFromFile("static/Tetris.wav");
	gameMusic.setLoop(true);
	gameMusic.play();

	// Game object load difficulty settings from SettingsScreen on initialization
	// User cannot modify difficulty during gameplay
	if(TetrisLoader::contains(TetrisLoader::SETTINGS)) {
		SettingsScreen* settings = dynamic_cast<SettingsScreen*>(*TetrisLoader::getScreen(TetrisLoader::SETTINGS));
		setDifficulty(settings->getDifficulty());
		gameMusic.setVolume(settings->getSoundVolume());
	} else {
		gameMusic.setVolume(50.f);
	}
	// Update the position of the preview tetromino
	updateCollisionPreview();
}

/*
	#Override : ICollectionScreen
	Handles the actual game ticks of Tetris.
	It is the place where the collision check happen. 
*/
void GameScreen::update() {
	if (m_state == GAMEOVER) {
		return; // no need for game ticks anymore
	}
	if (m_clock.getElapsedTime().asMilliseconds() > m_tickInterval) {
		if (gameMusic.getStatus() == sf::Music::Status::Paused) {
			gameMusic.play();
		}
		if (m_completedRows.size() > 0) {
			for (int& rowId : m_completedRows) {
				m_playfield.deleteRow(rowId);
			}

			m_completedRows.clear();
			updateCollisionPreview(); // Update Preview after completed lines are removed
		} else {
			m_currentTetromino.move(Tetromino::DOWN);

			// If the tetromino hit the ground or a block after moving down
			if (!isPosValid()) {
				// Move it back into a valid position
				m_currentTetromino.move(Tetromino::UP);

				// Handle the game mechanics following the collision
				handleCollision();
			}
		}
		// Start a new tick
		m_clock.restart();
	}
}

/*
	#Override : ICollectionScreen
	Draw method will be called directly before the next frame will
	displayed. It needs the actual window and font. Both are pointers.
	From here, all other components will be drawn (playfield, tetromino, text, etc).

	Example usage:
		window.clear();
		CollectionScreen.draw(&currentWindow, &currentFont);
		window.diplay();
*/
void GameScreen::draw(sf::RenderWindow* window, sf::Font* font) {
	m_playfield.drawGrid(window);
	m_playfield.drawTetromino(window, m_currentTetromino, false);
	m_playfield.drawTetromino(window, m_previewTetromino, false);
	m_playfield.drawTetromino(window, m_collisionPreview, true);
	m_score.draw(window, font);

	// print an nice GameOVer screen
	if (m_state == GAMEOVER) {
		const unsigned int BLOCK_SIZE{ (window->getSize().y- 2 * Playfield::s_OFFSET) / Playfield::s_ROWS };
		sf::Vector2f size(BLOCK_SIZE * Playfield::s_COLUMNS, window->getSize().y - 2 * Playfield::s_OFFSET);

		sf::RectangleShape shape;
		shape.setSize(size);
		shape.setPosition(Playfield::s_OFFSET, Playfield::s_OFFSET);
		shape.setFillColor(sf::Color(255, 150, 150, 150));
		window->draw(shape);

		sf::Text gameoverText("\t \t \t  GameOver! \nPress <RETURN> for Continue", *font, 50);
		gameoverText.setPosition(50.f, 400.f);
		window->draw(gameoverText);
	}
}

/*
	#Override : ICollectionScreen
*/
int GameScreen::close(GameCollection::ICollectionScreen** screen) {
	gameMusic.pause();
	*screen = *TetrisLoader::getScreen(TetrisLoader::SCREENS(m_nextScreen));
	return CONTINUE;
}

/*
	Sets the starting difficulty of the game.
	The difficulty corresponds to the level and influences the tickinterval, meaning the tetromino moves
	down faster the higher the level.
*/
void GameScreen::setDifficulty(int difficulty) {
	m_score.setStartLevel(difficulty);
	m_tickInterval = 1000 - (difficulty * 50);
}

/*
	Generates a random tetromino type out of Tetromino::TETROMINO_TYPE and returns it.
*/
Tetromino::TETROMINO_TYPE GameScreen::generateRandom() {
	Tetromino::TETROMINO_TYPE randomTetrominoType = static_cast<Tetromino::TETROMINO_TYPE>(rand() % Tetromino::END);
	return randomTetrominoType;
}

/*
	Updates the position of the collisionPreview-Tetromino.
	Has to be called after the player moved the tetromino or a new one spawned.

	Example usage:
	tetromino.move(Tetromino::Right);
	// check if valid
	updateCollisionPreview();
*/
void GameScreen::updateCollisionPreview() {
	m_collisionPreview = m_currentTetromino;

	// Move the preview until it collides with the ground or a block
	do {
		m_collisionPreview.move(Tetromino::DOWN);
	}  while (isPosValid(&m_collisionPreview));
	m_collisionPreview.move(Tetromino::UP); // Move tetromino back into a valid position
}

/*
	Handles the game mechanics following a collision of tetromino with the ground or a block.
	Includes adding it to the grid, deleting the completed row, increasing the score and 
	spawns a new tetromino.

	Example usage:
	if (!isPosValid())
		handleCollision();
*/
void GameScreen::handleCollision() {
    if (m_state == GAMEOVER) {
        return;
    }
	// Add the tetromino to the grid
	m_playfield.addTetromino(m_currentTetromino);

	// Check if gameover
	for (int x = 0; x < Playfield::s_COLUMNS; x++) {
		if (m_playfield.getColorOfField(1, x) != sf::Color::Black) {
			m_state = GameScreen::GAMEOVER;
			gameMusic.stop();
			if (m_score.isNewHighscore()) {
				TetrisLoader::erase(TetrisLoader::SCORE);
				TetrisLoader::addScreen(TetrisLoader::SCORE, new ScoreScreen(m_score, ScoreScreen::NEW_SCORE)); // user can write his name
			}
			// Stop game logic
			return;
		}
	}
	// Only check for completed rows again, if completed rows have been deleted
	if (m_completedRows.size() == 0) {

		// Check for completed rows
		m_completedRows = m_playfield.checkForCompletedRows();

		if (m_completedRows.size() > 0) {
			m_playfield.markCompletedRows(&m_completedRows, sf::Color::White);

			// Update the score (includes counting completed lines and level)
			m_score.update(m_completedRows.size());

			// Adjust difficulty (tickInterval) according to level
			m_tickInterval = 1000 - (m_score.getLevel() * 50);
		}
		// Start a new tick
		m_clock.restart();
	}
	// Spawn a new tetromino with the shape of the preview
	m_currentTetromino = Tetromino(m_previewTetromino.getType(), Tetromino::PLAYFIELD_POS);
	// Generate a new preview tetromino
	m_previewTetromino = Tetromino(generateRandom(), Tetromino::PREVIEW_POS);

	// Update the collision preview for the freshly spawned tetromino
	updateCollisionPreview();
}

/*
	#Override : ICollectionScreen
	Will called if KeyPressed or TextEntered Event get cached in Collection::run
	Param:
		sf::Event - Possible states of sf::Event.key.code:
					KeyPressed,
					TextEntered

*/
void GameScreen::handleEvent(const sf::Event sfevent) {
	// if game is gameover only allow to press return
	if (m_state == GAMEOVER) {
		if (sfevent.key.code == sf::Keyboard::Return) {
			m_running = false; // invoke close()
			m_nextScreen = TetrisLoader::SCORE;
			if (!TetrisLoader::contains(TetrisLoader::SCORE)) {
				// create new score screen if no exists
				TetrisLoader::addScreen(TetrisLoader::SCORE, new ScoreScreen(m_score));
			}
		} else {
			return;
		}
	}

	switch (sfevent.key.code) {
	case sf::Keyboard::Up:
	case sf::Keyboard::W:
		m_currentTetromino.rotate(Tetromino::FORWARD);
		if (!isPosValid())
			m_currentTetromino.rotate(Tetromino::BACKWARD);
		break;
	case sf::Keyboard::Left:
	case sf::Keyboard::A:
		m_currentTetromino.move(Tetromino::LEFT);
		if (!isPosValid())
			m_currentTetromino.move(Tetromino::RIGHT);
		break;
	case sf::Keyboard::Right:
	case sf::Keyboard::D:
		m_currentTetromino.move(Tetromino::RIGHT);
		if (!isPosValid())
			m_currentTetromino.move(Tetromino::LEFT);
		break;
	case sf::Keyboard::Down:
	case sf::Keyboard::S:
		m_currentTetromino.move(Tetromino::DOWN);
		m_clock.restart(); // Start a new tick
		break;
	case sf::Keyboard::Space:
		do {
			m_currentTetromino.move(Tetromino::DOWN);
		} while (isPosValid());
		m_currentTetromino.move(Tetromino::UP); // Move it back into a valid position
		handleCollision(); // Handle the game mechanics following the collision
		break;
	case sf::Keyboard::P:
		if (m_state == PAUSED) {
			m_state = GAME_STATE::PAUSED;
		} else {
			m_state = PLAYING;
		}
		break;
	case sf::Keyboard::Escape:
		m_running = false;
		m_nextScreen = TetrisLoader::MENU;
		break;
	default:
		break;
	}
	if (!isPosValid()) {
		m_currentTetromino.move(Tetromino::UP);
		handleCollision();
	}
	updateCollisionPreview();
}

/*
	Calls the method isPosValid(Tetromino* tetromino with the member variable
	m_currentTetromino. This method is just for clarity and defines the default 
	tetromino if someone want to know if the position is valid.
*/
bool GameScreen::isPosValid() {
	return isPosValid(&m_currentTetromino);
}

/*
	Returns a boolean if the position of the given tetromino-pointer
	is valid or not. Invalid means, the tetromino is somewhere where it
	should not be (outside the field or inside an another tetromino => collision).
	If this method returns true, everything is fine. 

	Example Usage: 
		Tetromino currentTetromino = Tetromino(...);
		currentTetromino.move(Tetromino::RIGHT);
		if (game.isPosValid(&tetromino))
			// ok
		else
			currentTetromino.move(Tetromino::LEFT);
			// position invalid! left wall? or something?
*/
bool GameScreen::isPosValid(Tetromino* tetromino) {
	const sf::Vector2i* pos = &tetromino->getPosition();
	const Tetromino::TetroShape* currentShape = &Tetromino::SHAPE_DATA[tetromino->getType()][tetromino->getRotation()];

	// other tetrominos
	// iterate the 4x4 tetroshape
	for (unsigned int y = 0; y < 4; y++) {
		for (unsigned int x = 0; x < 4; x++) {

			// if there is something other than zero, there is one part/block of the tetromino 
			if (currentShape[0][y][x] == 1) {
				// this position in the array + the position of the hole tetromino indicates 
				// a valid position in the color-grid of playfield.
				// if there is something other than black, a tetromino color was filled there before
				// => indicates a collision

				if (pos->x + x < 0)
					return false;
				else if (pos->x + x > Playfield::s_COLUMNS - 1)
					return false;
				else if (pos->y + y > Playfield::s_ROWS - 1)
					return false;

				if (m_playfield.getColorOfField(pos->y + y, pos->x + x) != sf::Color::Black)
					return false;
			}
		}
	}
	// return true if no if-condition is true
	return true;
}

const GameScreen::GAME_STATE& GameScreen::getGameState() {
	return m_state;
}

void GameScreen::setGameState(GameScreen::GAME_STATE state) {
	m_state = state;
}

void GameScreen::setSoundVolume(const float& volume) {
	gameMusic.setVolume(volume);
}

} /* namespace TetrisGame */