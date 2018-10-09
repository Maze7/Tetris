#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "../../FileIO/FileIO.h"

namespace FlappyBirdGame
{
	class FlappyBirdScore
	{
	public:
		FlappyBirdScore() : m_pipesPassed(0), m_highscoreList(5, 0) { init(); }
		~FlappyBirdScore() {}

		void draw(sf::RenderWindow* window, sf::Font* font);

		void update();
		void reset();

		const int& getPipesPassed() { return m_pipesPassed; }

		const std::vector<int>* getHighscoreList() { return &m_highscoreList; }

		bool isNewHighscore();
		void addToHighscoreList();

		void readHighscoreListFromFile();
		void writeHighscoreListToFile();

	private:
		std::vector<int> m_highscoreList;

		int m_pipesPassed;
		sf::Text m_pipesPassedText;
		
		void init();
	};

}


