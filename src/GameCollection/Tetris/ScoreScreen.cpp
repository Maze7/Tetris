#include "ScoreScreen.h"
#include "TetrisLoader.h"

using namespace TetrisGame;

ScoreScreen::ScoreScreen(TetrisScore& score, STATES scoreState) :
	m_hover(ENTRYS::BACK), 
	m_currentState(ENTRYS::BACK), 
	m_state(scoreState),
	m_nextScreen(EXIT_APP), 
	m_score(score), 
	m_background(sf::Texture())
{
	if (!m_background.loadFromFile(TetrisGame::TetrisMenu::s_BACKGROUND_PATH))
	{
		std::cerr << "[ERROR] [TetrisGame::ScoreScreen] loading bg picture failed" << std::endl;
	}
}

void ScoreScreen::handleEvent(const sf::Event sfevent)
{
	// no new highscore => only back is displayed so return means go back
	if (m_state == SHOW_SCORE && sfevent.key.code == sf::Keyboard::Return) {
		m_running = false;
		m_nextScreen = TetrisLoader::MENU;
		return;
	// if user focused "NAME" (only possible if m_state is on NEW_SCORE, implicit condition) let him write his name 
	} else if (m_hover == NAME && sfevent.type == sf::Event::TextEntered) {
		userName += sfevent.text.unicode;
	// if NEW the user is able to swtich between menu points 
	} else if (m_state == NEW_SCORE) {
		int newHover;
		switch (sfevent.key.code)
		{
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
		case sf::Keyboard::Return:
			//TODO
			if (m_hover == BACK) {
				m_running = false; // invoke close
				m_nextScreen = TetrisLoader::MENU; 
			}
			else if (m_hover == NAME && !userName.empty()) {
				m_score.writeHighscoreListToFile();
			}
			break;
		}
	}
}

void ScoreScreen::draw(sf::RenderWindow* window, sf::Font* font)
{

	sf::Text highscores[4]; // show 4 recent highscores
	sf::Vector2f pos(280.f, 230.f);
	std::string var = std::to_string(m_score.getHighscoreList()[0][0].score);
	sf::Text highscoreText("Current Highscore: " + var, *font, 35);
	highscoreText.setPosition(280.f, 160.f);

	for (auto& score : highscores) {
		var = std::to_string(m_score.getHighscoreList()[0][0].score);
		score = sf::Text("Score: " + var, *font, 35);
		score.setPosition(pos);
		pos.y = pos.y + 50;
		window->draw(score);
	}

	sf::Sprite sprite;
	sprite.setTexture(m_background);
	sprite.setColor(sf::Color(255, 255, 255, 150));
	sf::Text back("Back", *font, 35);

	if (m_state == NEW_SCORE) { // user can write his name
		sf::Text newScore("YOU HAVE THE NEW HIGHSCORE", *font, 35);
		newScore.setPosition(280.f, 125.f);
		newScore.setFillColor({ 255, 155, 155, 155 });
		window->draw(newScore);

		sf::Text text("Type in your name: " + userName, *font, 35);
		pos.y = pos.y + 70;
		text.setPosition(pos);

		if (m_hover == NAME) {
			text.setFillColor(sf::Color(255, 0, 0, 255));
			back.setFillColor(sf::Color(255, 255, 255, 255));
		}
		else {
			text.setFillColor(sf::Color(255, 255, 255, 255));
			back.setFillColor(sf::Color(255, 0, 0, 255));
		}
		window->draw(text);
	}
	else {
		back.setFillColor(sf::Color(255, 0, 0, 255));
	}

	back.setPosition(pos.x, pos.y + 100);
	window->draw(back);
	window->draw(highscoreText);
	window->draw(sprite);
}

int ScoreScreen::close(ICollectionEntry** screen)
{
	*screen = *TetrisLoader::getScreen(TetrisLoader::SCREENS(m_nextScreen));
	return CONTINUE; // There is no exit option in this menu
}
