#include "Collection.h"
#include <iostream>

std::map<std::string, std::vector<GameCollection::ICollectionEntry*>*> GameCollection::Collection::s_entrys = std::map<std::string, std::vector<GameCollection::ICollectionEntry*>*>();

GameCollection::Collection::~Collection()
{
	for (auto& modulScreens : s_entrys) {
		for (auto& screen : *modulScreens.second) { // vector
			delete screen;
		}
	}
}

/*
	This is the main method of GameCollection
*/
int GameCollection::Collection::run(sf::RenderWindow& window, sf::Font& font)
{
	sf::Event event;
	MenuEntry mainMenu;
	ICollectionEntry* currentScreen;

	// Helpers
	std::vector<ICollectionEntry*>* entrysOfModule;
	int screenIndex = 0;

	currentScreen = &mainMenu;
	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::TextEntered || event.type == sf::Event::KeyPressed)
				currentScreen->handleEvent(event);
		}

		if (!currentScreen->isRunning()) {
			screenIndex = currentScreen->close(); // close returns vector index which screen should displayed next
			switch (screenIndex)
			{
			case currentScreen->EXIT_APP:
				window.close();
				return EXIT_SUCCESS;
				break;

			case currentScreen->MAIN_MENU:
				currentScreen = &mainMenu;
				currentScreen->setRunning();
				break;

			default:
				entrysOfModule = s_entrys.at(mainMenu.getCurrentName());
				currentScreen = entrysOfModule[0][screenIndex];
				currentScreen->setRunning();
				break;
			}
		}

		currentScreen->handleTime();
		window.clear();
		currentScreen->draw(&window, &font);
		window.display();
	}
	return EXIT_FAILURE;
}

/*
	Static method is needed to load Screens/entrys. 
	A modul loader can store screens with a matching name inside s_entrys. 

	Param:moduleName specify the name of the hole modul. Each modul can have n screens which
	are stored in param:screen 
	It is recommended to set modulName equals to the used namespace. 
*/
void GameCollection::Collection::addModuleEntrys(std::string moduleName, std::vector<GameCollection::ICollectionEntry*>* screens)
{
	s_entrys.insert(std::make_pair(moduleName, screens));
}

/*
	Getter for s_screens. Returns a pointer to hole map of std::vector<ICollectionEntrys*>*
*/
const std::map<std::string, std::vector<GameCollection::ICollectionEntry*>*>* const GameCollection::Collection::getEntrys()
{
	return &s_entrys;
}
