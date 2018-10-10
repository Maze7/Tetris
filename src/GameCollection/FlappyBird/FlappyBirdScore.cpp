#include "FlappyBirdScore.h"
/*
	Increases the score and updates the corresponding sf::Text.

	Example usage:
	if (// bird passed a pipe) {
		score.update();
	}
*/
void FlappyBirdGame::FlappyBirdScore::update()
{
	m_pipesPassed++;
	m_pipesPassedText.setString("Pipes passed: " + std::to_string(m_pipesPassed));
}

/*
	Checks if the achieved score is a new highscore.

	Example usage:
	// gameover
	if (score.isNewHighscore())
		// add the score to the list
*/
bool FlappyBirdGame::FlappyBirdScore::isNewHighscore()
{
	return m_pipesPassed > m_highscoreList[m_highscoreList.size() - 1];
}

/*
Adds the current score to the m_highscoreList. The current score replaces the last element
of the m_highscoreList. Afterwards the list gets sorted.
*/
void FlappyBirdGame::FlappyBirdScore::addToHighscoreList()
{
	m_highscoreList.at(m_highscoreList.size() - 1) = m_pipesPassed;
	std::sort(m_highscoreList.begin(), m_highscoreList.end());
}

/*
	Reads the highscores from the file and saves them in the m_highscoreList
	Should be called in the constructor of this class (FlappyBirdScore).
*/
void FlappyBirdGame::FlappyBirdScore::readHighscoreListFromFile()
{
	try {
		std::vector<std::string> v_input = FileIO::readFile("FlappyBirdHighscores.txt");

		for (int i = 0; i < m_highscoreList.size(); i++) {
			m_highscoreList.at(i) = std::stoi(v_input.at(i));
		}
	}
	catch (Exceptions::FileExceptions::FileNotFoundException const &e)
	{
		std::cout << e.what() << std::endl;
	}
}

/*
	Writes the m_highscoreList to a file.
	Should be called before closing the application.
*/
void FlappyBirdGame::FlappyBirdScore::writeHighscoreListToFile()
{
	std::string output;

	for (int highscore : m_highscoreList) {
		output += std::to_string(highscore) + "\n";
	}

	// Write to file
	try {
		FileIO::writeFile(output, "FlappyBirdHighscores.txt");
	}
	catch (Exceptions::FileExceptions::FileWriteException const &e) {
		std::cout << e.what() << std::endl;
	}
}

void FlappyBirdGame::FlappyBirdScore::draw(sf::RenderWindow * window, sf::Font * font)
{
	m_pipesPassedText.setFont(*font);
	window->draw(m_pipesPassedText);
}

/*
	Sets up the Sf::Text's of this class.
	Should be called in the constructor of this class (FlappyBirdScore).
*/
void FlappyBirdGame::FlappyBirdScore::init()
{
	m_pipesPassedText.setCharacterSize(32);
	m_pipesPassedText.setFillColor(sf::Color::White);
	m_pipesPassedText.setPosition(500, 500);
	m_pipesPassedText.setString("Pipes passed: " + std::to_string(m_pipesPassed));
}