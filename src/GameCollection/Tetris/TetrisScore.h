#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "../../FileIO/FileIO.h"

namespace TetrisGame 
{
	struct Highscore
	{
		Highscore(int score, int level, int lineCount)
			: score(score)
			, level(level)
			, lineCount(lineCount)
		{}
		
		const int getScore() { return score; }
		const int getLevel() { return level; }
		const int getLineCount() { return lineCount; }

	private:
		int score;
		int level;
		int lineCount;
	};

	class TetrisScore
	{
	public:
		TetrisScore();
		~TetrisScore() {};

		void draw(sf::RenderWindow* window, sf::Font* font);
		void update(int completedRowCount);
		const std::vector<Highscore>* getHighscoreList() { return &m_highscoreList; }

		const int getScore();
		const int getLevel();
		const int getLineCount();

		bool isNewHighscore();
		void addToHighscoreList();

		void readHighscoreListFromFile();
		void writeHighscoreListToFile();

	private:
		std::vector<Highscore> m_highscoreList;

		int m_score;
		sf::Text m_scoreText;

		int m_level;
		sf::Text m_levelText;

		int m_lineCount;
		sf::Text m_lineCountText;

		void init();
	};
}

