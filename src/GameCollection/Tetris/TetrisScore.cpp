#include "TetrisScore.h"

TetrisGame::TetrisScore::TetrisScore()
	: m_highscoreList(5, Highscore{0, 0, 0})
	, m_score(0)
	, m_level(1)
	, m_lineCount(0)
{
	init();
	readHighscoreListFromFile();
}

/*
	Reads the highscores from the file and saves them in the m_highscoreList
	Should be called in the constructor of this class (TetrisScore).
*/
void TetrisGame::TetrisScore::readHighscoreListFromFile()
{
	try
	{
		std::vector<std::string> v_input = FileIO::readFile("Highscores.txt");
		int i = 0;

		for (auto& highscore : m_highscoreList) {
				highscore = Highscore {std::stoi(v_input[i]), std::stoi(v_input[i + 1]), std::stoi(v_input[i + 2])};
				i += 3; // 3 is the amount of lines that belong to a highscore (score, level, linecount)
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
void TetrisGame::TetrisScore::writeHighscoreListToFile()
{
	std::string output;

	for (auto const& highscore : m_highscoreList)
	{
		output += std::to_string(highscore.score) + "\n" + std::to_string(highscore.level) + "\n" + std::to_string(highscore.lineCount) + "\n";
	}

	// Write to file
	try {
		FileIO::writeFile(output, "Highscores.txt");
	}
	catch (Exceptions::FileExceptions::FileWriteException const &e) {
		std::cout << e.what() << std::endl;
	}
}

/*
	Draws the score texts in the given window with the given font.
*/
void TetrisGame::TetrisScore::draw(sf::RenderWindow* window, sf::Font* font)
{
	m_levelText.setFont(*font);
	m_scoreText.setFont(*font);
	m_lineCountText.setFont(*font);

	window->draw(m_levelText);
	window->draw(m_scoreText);
	window->draw(m_lineCountText);
}

/*
	Increases each score metric and the corresponding sf::Text depending on rows completed
*/
void TetrisGame::TetrisScore::update(int completedRowCount)
{
	// Update the line count
	m_lineCount += completedRowCount;

	// Increase the score depending on rows completed
	switch (completedRowCount)
	{
	case 1:
		m_score += 40 * m_level;
		break;
	case 2:
		m_score += 100 * m_level;
		break;
	case 3:
		m_score += 300 * m_level;
		break;
	case 4:
		m_score += 1200 * m_level;
		break;
	default:
		break;
	}

	// Update the sf::Text's that are displayed on screen
	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_levelText.setString("Level: " + std::to_string(m_level));
	m_lineCountText.setString("Lines: " + std::to_string(m_lineCount));
}

const int& TetrisGame::TetrisScore::getScore()
{
	return m_score;
}

const int& TetrisGame::TetrisScore::getLevel()
{
	return m_level;
}

const int& TetrisGame::TetrisScore::getLineCount()
{
	return m_lineCount;
}

/*
	Checks if the achieved score is a new highscore.

	Example usage:
	// gameover 
	if (m_score.isNewHighscore()) 
		// add the score to the list
*/
bool TetrisGame::TetrisScore::isNewHighscore()
{
	return m_score > m_highscoreList[m_highscoreList.size() - 1].score;
}

/*
	Adds the current score to the m_highscoreList. The current score replaces the last element
	of the m_highscoreList. Afterwards the list gets sorted.
*/
void TetrisGame::TetrisScore::addToHighscoreList()
{
	// Add new highscore as last element to the list
	m_highscoreList[m_highscoreList.size() - 1] = Highscore{m_score, m_level, m_lineCount};

	// Custom sort algorithm - Sorts by score 
	auto sortByScore = [](Highscore& left, Highscore& right) { return left.score > right.score; };

	// Sort the list with the custom sort algorithm
	std::sort(m_highscoreList.begin(), m_highscoreList.end(), sortByScore);
}

/*
	Sets up the position, color and size of the sf::Texts.
	Should be called in the constructor of this class (TetrisScore).
*/
void TetrisGame::TetrisScore::init()
{
	m_levelText.setCharacterSize(32);
	m_scoreText.setCharacterSize(32);
	m_lineCountText.setCharacterSize(32);

	m_levelText.setFillColor(sf::Color::White);
	m_scoreText.setFillColor(sf::Color::White);
	m_lineCountText.setFillColor(sf::Color::White);

	m_levelText.setPosition(500, 400);
	m_scoreText.setPosition(500, 500);
	m_lineCountText.setPosition(500, 600);

	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_levelText.setString("Level: " + std::to_string(m_level));
	m_lineCountText.setString("Lines: " + std::to_string(m_lineCount));
}


