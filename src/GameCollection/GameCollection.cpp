#include <SFML/Graphics.hpp>
#include "ICollectionEntry.h"
#include "Tetris/TetrisGame.h"
#include "FlappyBird\FlappyBirdGame.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "GameCollection");
	sf::Font font;
	sf::Event event;

	if (!font.loadFromFile("big_noodle_titling.ttf"))
	{
		std::cout << "Couldn't load font." << std::endl;
		return 1;
	}

	srand(time(NULL));

	//TetrisGame::Game game;
	FlappyBirdGame::FlappyBirdGame game;
	GameCollection::ICollectionEntry* entry = &game;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
				entry->handleEvent(event);
		}
		entry->handleTime();
		window.clear();
		entry->draw(&window, &font);
		window.display();
	}

	entry->close();
}