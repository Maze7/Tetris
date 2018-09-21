#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collection.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "GameCollection");
	sf::Font font;

	// Todo ioutils
	if (!font.loadFromFile("big_noodle_titling.ttf")) {
		std::cerr << "[ERROR] [MAIN] Could not load font" << std::endl;
		return 1;
	}

	srand(time(NULL));
	GameCollection::Collection col;
	return col.run(window, font);
}