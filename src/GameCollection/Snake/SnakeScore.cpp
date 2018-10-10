#include "SnakeScore.h"

void SnakeGame::SnakeScore::draw(sf::RenderWindow * window, sf::Font * font)
{
	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_scoreText.setFont(*font);
	window->draw(m_scoreText);
}

/*
	Increases the score.

	Example usage:
	if (//player scored) 
		score.update();
*/
void SnakeGame::SnakeScore::update()
{
	m_score++;
}

/*
	Resets the current score.
	Should be called before a new game is started.
*/
void SnakeGame::SnakeScore::reset()
{
	m_score = 0;
}

/*
	Checks if the achieved score is a new highscore.

	Example usage:
	// gameover
	if (m_score.isNewHighscore())
		// add the score to the list
*/
bool SnakeGame::SnakeScore::isNewHighscore()
{
	return m_score > m_highscoreList[m_highscoreList.size() - 1];;
}

/*
	Adds the current score to the m_highscoreList. The current score replaces the last element
	of the m_highscoreList. Afterwards the list gets sorted.
*/
void SnakeGame::SnakeScore::addToHighscoreList()
{
	m_highscoreList.at(m_highscoreList.size() - 1) = m_score;
	std::sort(m_highscoreList.begin(), m_highscoreList.end());
}

/*
	Reads the highscores from the file and saves them in the m_highscoreList
	Should be called in the constructor of this class (SnakeScore).
*/
void SnakeGame::SnakeScore::readHighscoreListFromFile()
{
	try {
		std::vector<std::string> v_input = FileIO::readFile("SnakeHighscores.txt");

		if (v_input.size() == m_highscoreList.size()) {
			try {
				for (int i = 0; i < v_input.size(); i++) {
					m_highscoreList.at(i) = std::stoi(v_input.at(i));
				}
			}
			catch (std::invalid_argument &e) {
				std::cout << "Invalid Argument in Highscores.txt" << std::endl;
			}
			catch (std::out_of_range &e) {
				std::cout << "Argument in Highscores.txt is out of range" << std::endl;
			}
		}
	}
	catch (Exceptions::FileExceptions::FileNotFoundException const &e) {
		std::cout << e.what() << std::endl;
	}
}

/*
	Writes the m_highscoreList to a file.
	Should be called before closing the application.
*/
void SnakeGame::SnakeScore::writeHighscoreListToFile()
{
	std::string output;

	for (auto const& highscore : m_highscoreList) {
		output += std::to_string(highscore) + "\n";
	}

	// Write to file
	try {
		FileIO::writeFile(output, "SnakeHighscores.txt");
	}
	catch (Exceptions::FileExceptions::FileWriteException const &e) {
		std::cout << e.what() << std::endl;
	}
}

/*
	Sets up the position, color and size of the sf::Texts.
	Should be called in the constructor of this class (SnakeScore).
*/
void SnakeGame::SnakeScore::init()
{
	m_scoreText.setCharacterSize(32);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setPosition(220, 520);
}
