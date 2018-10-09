#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "../../FileIO/FileIO.h"

namespace TetrisGame 
{
	class TetrisScore
	{
	public:
		struct Highscore
		{
			std::string playerName;
			int score, level, lineCount;
		};
		
		TetrisScore();
		~TetrisScore() {};

		void draw(sf::RenderWindow* window, sf::Font* font);
		void update(int completedRowCount);
		const std::vector<Highscore>* getHighscoreList() { return &m_highscoreList; }

		const std::string& getPlayerName();
		void setPlayerName(const std::string& playerName);

		const int& getScore();
		const int& getLevel();
		const int& getLineCount();

		bool isNewHighscore();
		void addToHighscoreList();

		void readHighscoreListFromFile();
		void writeHighscoreListToFile();

	private:
		std::vector<Highscore> m_highscoreList;

		std::string m_playerName;

		int m_score;
		sf::Text m_scoreText;

		int m_level;
		sf::Text m_levelText;

		int m_lineCount;
		sf::Text m_lineCountText;

		void init();
	};
}

