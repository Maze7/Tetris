#include "Collection.h"
#include <iostream>

namespace GameCollection {

// init for static elements
std::map<std::string, ICollectionScreen*> Collection::s_entrys = std::map<std::string, ICollectionScreen*>();

/*
	Iterates through s_entrys and deletes every pointer. 
*/
Collection::~Collection() {
	for (auto& modulScreen : s_entrys) {
		delete modulScreen.second;
	}
}

/*
	Contains the main-loop of GameCollection
	Params: sf::RenderWindow& where everything should displayed
			sf::Font& the font will used everywhere in Collection.h
*/
int Collection::run(sf::RenderWindow& window, sf::Font& font) {

	MainMenuScreen mainMenu;
	ICollectionScreen* currentScreen;

	// helpers - will overwritten
	int returnValue = EXIT_SUCCESS;
	sf::Event event;

	currentScreen = &mainMenu;

	// main loop
	while (window.isOpen()) {

		// event loop
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::TextEntered || event.type == sf::Event::KeyPressed) {
				currentScreen->handleEvent(event);
			}
		}

		if (!currentScreen->isRunning()) {
			returnValue = currentScreen->close(&currentScreen);

			// exit application if currentScreen is nullptr (close method can do this)
			if (currentScreen == nullptr)
				exit(EXIT_FAILURE);
			
			// check which action needs to perform depends on return value of close()
			switch (returnValue) {
			case currentScreen->MAIN_MENU:
				currentScreen = &mainMenu;
				currentScreen->setRunning();
				break;

			case currentScreen->CONTINUE:
				currentScreen->setRunning();
				break;

			case currentScreen->EXIT_APP:
			default:
				return returnValue;
				break;
			}
		}

		currentScreen->update();
		window.clear();
		currentScreen->draw(&window, &font);
		window.display();
	}
	return EXIT_FAILURE;
}

/*
	Static method is needed to load Screens/entrys. 
	A module-loader needs to set an ICollectionEntry. This will shown 
	if the user choose this module. It can be a menu (in this case the 
	menu needs to handle other screens) or a hole game. 


	Param:
		std::string the name of module - 	It is recommended to set modulName equals to the used namespace. 
		ICollectionEntry* an compatible GameCollection screen.
	Example Usage: (Quick and Dirty with Game-Loader)
		class ExampleGameLoader {
			ExampleGameLoader() { Collection::addModuleEntrys("ExampleGame", new ExampleGame()); }
		};
		namspace { static const ExampleGameLoader loading; } // invoke Constructor in private namespace
*/
void Collection::addModuleEntrys(std::string moduleName, ICollectionScreen* screen) {
	s_entrys.insert(std::make_pair(moduleName, screen));
}

/*
	const Getter for s_screens. Returns a pointer to hole map std::map<std::string, ICollectionEntry*>*
*/
const std::map<std::string, ICollectionScreen*>* const Collection::getEntrys() {
	return &s_entrys;
}

} /* namespace GameCollection */