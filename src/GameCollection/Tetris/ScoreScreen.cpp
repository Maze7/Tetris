#include "ScoreScreen.h"
#include "TetrisLoader.h"

using namespace TetrisGame;

ScoreScreen::ScoreScreen(TetrisScore& score, STATES scoreState) :
			m_hover(((scoreState == NEW_SCORE) ? NAME : BACK)), // focuse name field if user should type
			m_currentState(m_hover),
			m_state(scoreState),
			m_nextScreen(EXIT_APP),
			m_score(score),
			m_background(sf::Texture()) {

	if (!m_background.loadFromFile(TetrisGame::TetrisMenu::s_BACKGROUND_PATH))
		std::cerr << "[ERROR] [TetrisGame::ScoreScreen] loading bg picture failed" << std::endl;
}

void ScoreScreen::handleEvent(const sf::Event sfevent) {
	// no new highscore => only back is displayed so return means go back
	if (m_state == SHOW_SCORE && sfevent.key.code == sf::Keyboard::Return) {
		m_running = false;
		m_nextScreen = TetrisLoader::MENU;
		return;

	// if user focused "NAME" (only possible if m_state is on NEW_SCORE, implicit condition) let him write his name
	} else if (m_hover == NAME && sfevent.type == sf::Event::TextEntered) {
	    if (sfevent.text.unicode == 8) {
	        if (userName.length()) {//If the string doesn't have any char, don't do anything
	        	userName = userName.substr(0, userName.size()-1);
	        }
	    } else {//Don't add any character while delete one
	        if(userName.length() < 16) {
	        	userName += sfevent.text.unicode;
	        }
	    }
	} else if (m_state == NEW_SCORE && sfevent.type == sf::Event::KeyPressed) {
		int newHover;
		switch (sfevent.key.code) {
		case sf::Keyboard::Up:
			if (m_hover == 0)
				m_hover = ENTRYS(END - 1);
			else
				m_hover = ENTRYS(m_hover - 1);
			break;
		case sf::Keyboard::Down:
			newHover = (m_hover + 1) % END;
			m_hover = ENTRYS(newHover);
			break;
		case sf::Keyboard::Escape:
			m_running = false;
			m_nextScreen = TetrisLoader::MENU;
			break;
		case sf::Keyboard::Backspace:
		case sf::Keyboard::Delete:
			if (userName.size() > 0) {
				userName = userName.substr(0, userName.size()-1); // delete one char
			}
			break;
		case sf::Keyboard::Return:
			if (m_hover == BACK) {
				m_running = false; // invoke close
				m_state = SHOW_SCORE; // user cant type his name next time
				m_nextScreen = TetrisLoader::MENU; 
			} else if (m_hover == NAME && !userName.empty()) {
				m_score.setPlayerName(userName);
				m_score.addToHighscoreList();
				m_score.writeHighscoreListToFile();
				m_state = SHOW_SCORE;
			}
			break;
		default:
			break;
		}
	}
}

void ScoreScreen::draw(sf::RenderWindow* window, sf::Font* font) {

	sf::Text highscores[4]; // show 4 recent highscores
	sf::Vector2f pos(280.f, 230.f);
	std::string scoreString = std::to_string(m_score.getHighscoreList()[0][0].score);
	sf::Text highscoreText("Current Highscore: " + scoreString + " (" + m_score.getHighscoreList()[0][0].playerName + ")", *font, 35);
	highscoreText.setPosition(280.f, 160.f);

	for (int i = 0; i < 4 ; i++) {
		scoreString = std::to_string(m_score.getHighscoreList()[0][i + 1].score);
		highscores[i] = sf::Text("Score: " + scoreString + " (" + m_score.getHighscoreList()[0][i + 1].playerName + ")", *font, 35);
		highscores[i].setPosition(pos);
		pos.y = pos.y + 50;
		window->draw(highscores[i]);
	}

	sf::Sprite sprite;
	sprite.setTexture(m_background);
	sprite.setColor(sf::Color(255, 255, 255, 150));
	sf::Text back("Back", *font, 35);

	if (m_state == NEW_SCORE) { // user can write his name
		sf::Text newScore("YOU HAVE REACHED: " + std::to_string(m_score.getScore()), *font, 35);
		newScore.setPosition(280.f, 125.f);
		newScore.setFillColor({ 255, 155, 155, 155 });
		window->draw(newScore);

		sf::Text text("Type in your name: " + userName, *font, 35);
		pos.y = pos.y + 70;
		text.setPosition(pos);

		if (m_hover == NAME) {
			text.setFillColor(sf::Color(255, 0, 0, 255));
			back.setFillColor(sf::Color(255, 255, 255, 255));
		} else {
			text.setFillColor(sf::Color(255, 255, 255, 255));
			back.setFillColor(sf::Color(255, 0, 0, 255));
		}
		window->draw(text);
	} else {
		back.setFillColor(sf::Color(255, 0, 0, 255));
	}

	back.setPosition(pos.x, pos.y + 100);
	window->draw(back);
	window->draw(highscoreText);
	window->draw(sprite);
}

int ScoreScreen::close(ICollectionEntry** screen) {
	*screen = *TetrisLoader::getScreen(TetrisLoader::SCREENS(m_nextScreen));
	return CONTINUE; // There is no exit option in this menu
}
