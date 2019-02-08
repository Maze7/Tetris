#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collection.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "GameCollection");
	window.setFramerateLimit(60);
	sf::Font font;

	if (!font.loadFromFile("static/BebasNeueBold.ttf")) {
		std::cerr << "[ERROR] [MAIN] Could not load font" << std::endl;
		return 1;
	}

	srand(time(NULL));
	GameCollection::Collection* col = new GameCollection::Collection();
	int returnT =  col->run(window, font);
	delete col;
	return returnT;
}
