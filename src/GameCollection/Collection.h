#pragma once
#include <SFML/Graphics.hpp>
#include "Tetris/Game.h"
#include "ICollectionEntry.h"
#include "Menu/MenuEntry.h"

namespace GameCollection
{
	typedef std::map<std::string, ICollectionEntry*> CollectionEntrys;
	
	class Collection
	{
	private:
		static CollectionEntrys s_entrys;

	public:
		Collection() {};

		/*
		 * Deletes every pointer in s_entrys
		 */
		~Collection();

		/*
		 * Contains the "main"lopp of GameCollection
  		 */
		int run(sf::RenderWindow& window, sf::Font& font);

		/*
		 * Returns a pointer to member s_entrys
		 * Type: std::map<std::string, std::vector<ICollectionEntry*>*>
		 */
		static const CollectionEntrys* const getEntrys();

		/*
		 * Used to add a new module to GameCollection. The (first) screen of each module 
		 * needs to be set on startup. 
		 */
		static void addModuleEntrys(std::string modulName, ICollectionEntry* screen);
	};
}