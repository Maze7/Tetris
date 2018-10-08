#ifndef SRC_GAMECOLLECTION_TETRIS_SCORESCREEN_H_
#define SRC_GAMECOLLECTION_TETRIS_SCORESCREEN_H_
#include "../ICollectionEntry.h"
#include "TetrisScore.h"
#include <SFML/Graphics.hpp>

namespace TetrisGame
{
	class ScoreScreen : public GameCollection::ICollectionEntry
	{
	private:
		/* 	TYPE_SCORE allows to see scores and makes a textbox
			available where the user can type in his name.
			If the ScoreScreen is SHOW_SCORE state, only the past
			highscore will displayed with no other option.
			TYPE_SCORE should set if the user got a new highscore.
		*/
		enum STATES { NEW_SCORE = 0, SHOW_SCORE = 1 };
		enum ENTRYS { NAME = 0, BACK = 1, END = 2 };

		ENTRYS m_currentState;
		TetrisScore& m_score;
		STATES m_state;
		ENTRYS m_hover;
		sf::Texture m_background;

		std::string userName;

		int m_nextScreen;
	public:
		ScoreScreen(TetrisScore& score);
		~ScoreScreen() {};

		void handleEvent(const sf::Event sfevent);
		void draw(sf::RenderWindow* window, sf::Font* font);
		int close(ICollectionEntry** screen);
	};
}
#endif /* SRC_GAMECOLLECTION_TETRIS_SCORESCREEN_H_ */

