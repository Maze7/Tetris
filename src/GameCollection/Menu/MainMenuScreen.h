#pragma once
#include "../ICollectionScreen.h"
#include <SFML/Graphics.hpp>
#include "../Collection.h"


/*
	This Class loads all entrys inside Collection::s_entrys
	and display them, so the user can decide which module should
	start. 
	There is no need to change something in this class, if there is 
	a new modul (=map entry). 
*/
class MainMenuScreen : public GameCollection::ICollectionScreen
{
private:
	std::string m_currentName;
	std::vector<std::string> m_entryNames;
	int m_hover;
	sf::Texture m_background;

public:
	MainMenuScreen();
	~MainMenuScreen() {};

	void handleEvent(const sf::Event sfevent);
	void draw(sf::RenderWindow* window, sf::Font* font);
	const std::string& getCurrentName();
	int close(ICollectionScreen** screen);
};

