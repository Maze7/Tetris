#include "SnakeScoreScreen.h"
#include <SFML/Graphics.hpp>
#include "SnakeLoader.h"

namespace SnakeGame {

SnakeScoreScreen::SnakeScoreScreen(SnakeScore& score) :
			m_score(score) {

}

void SnakeScoreScreen::handleEvent(const sf::Event sfevent) {
	if (sfevent.key.code == sf::Keyboard::Return
			|| sfevent.key.code == sf::Keyboard::Escape
			|| sfevent.key.code == sf::Keyboard::Space) {
		m_running = false;
	}
}

void SnakeScoreScreen::draw(sf::RenderWindow* window, sf::Font* font) {
	constexpr int scoreArray{5};
	sf::Text scores[scoreArray];
	sf::Vector2f pos(280.f, 110.f);

	for (int i = 0; i < scoreArray; i++) {
		if (!i) { // i == 0
			scores[i] = sf::Text("Current Highscore: " + std::to_string(m_score.getHighscoreList()[0][i]), *font, 35);
		} else {
			scores[i] = sf::Text("Score: " + std::to_string(m_score.getHighscoreList()[0][i]) , *font, 35);
		}
		scores[i].setPosition(pos);
		pos.y = pos.y + 60;
		window->draw(scores[i]);
	}
	sf::Text backText("Back", *font, 50);
	pos.y = pos.y + 130;
	backText.setPosition(pos);
	backText.setFillColor(sf::Color{255,0,0,255});
	window->draw(backText);
}

int SnakeScoreScreen::close(ICollectionScreen** screen) {
	*screen = GameCollection::Collection::getEntrys()->at(SnakeLoader::MODUL_NAME);
	return CONTINUE; // There is no exit option in this menu
}

} /* namespace SnakeGame */
