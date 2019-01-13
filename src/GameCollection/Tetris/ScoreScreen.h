#ifndef SRC_GAMECOLLECTION_TETRIS_SCORESCREEN_H_
#define SRC_GAMECOLLECTION_TETRIS_SCORESCREEN_H_
#include "TetrisScore.h"
#include <SFML/Graphics.hpp>
#include "../ICollectionScreen.h"

namespace TetrisGame {

class ScoreScreen : public GameCollection::ICollectionScreen {
public:
	/* 	NEW_SCORE allows to see scores and makes a textbox
		available where the user can type his name. It would
		safed to a textfile.
		If the ScoreScreen is in SHOW_SCORE state, only a few past
		highscores will displayed with no other options.
		TYPE_SCORE should set if the user got a new highscore.
	*/
	enum STATES { NEW_SCORE = 0, SHOW_SCORE = 1 };

private:
	enum ENTRYS { NAME = 0, BACK = 1, END = 2 };

	ENTRYS m_currentState;
	TetrisScore& m_score;
	STATES m_state;
	ENTRYS m_hover;
	sf::Texture m_background;

	std::string userName;

	int m_nextScreen;
public:
	ScoreScreen(TetrisScore& score, STATES scoreState);
	ScoreScreen(TetrisScore& score) : ScoreScreen(score, SHOW_SCORE) {}
	~ScoreScreen() {};

	void handleEvent(const sf::Event sfevent);
	void draw(sf::RenderWindow* window, sf::Font* font);
	int close(ICollectionScreen** screen);
};

} /* namespace TetrisGame */
#endif /* SRC_GAMECOLLECTION_TETRIS_SCORESCREEN_H_ */

