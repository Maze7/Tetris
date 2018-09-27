#pragma once
#include "../ICollectionEntry.h"
#include <SFML/Graphics.hpp>
#include "../Collection.h"


/*
	This Class loads all entrys inside Collection::s_entrys
	and display them, so the user can decide which module should
	start. 
	There is no need to change something in this class, if there is 
	a new modul (=map entry). 
*/
class MenuEntry : public GameCollection::ICollectionEntry
{
private:
	std::string m_currentName;
	std::vector<std::string> m_entryNames;
	int m_hover;

public:
	MenuEntry();
	~MenuEntry() {};

	void handleEvent(const sf::Event sfevent);
	void draw(sf::RenderWindow* window, sf::Font* font);
	const std::string& getCurrentName() { return m_currentName; } // todo: put in cpp file
	int close();
};
