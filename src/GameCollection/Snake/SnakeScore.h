#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "../../FileIO/FileIO.h"

namespace SnakeGame
{
	class SnakeScore
	{
	public:
		SnakeScore() : m_score(0), m_highscoreList(5, 0) { init(); }
		~SnakeScore(){}

		void draw(sf::RenderWindow* window, sf::Font* font);

		void update();
		void reset();

		const int& getSnakeSize() { return m_score; }

		const std::vector<int>* getHighscoreList() { return &m_highscoreList; }

		bool isNewHighscore();
		void addToHighscoreList();

		void readHighscoreListFromFile();
		void writeHighscoreListToFile();


	private:
		std::vector<int> m_highscoreList;

		int m_score;
		sf::Text m_scoreText;

		void init();
	};
}


