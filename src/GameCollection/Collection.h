#pragma once
#include <SFML/Graphics.hpp>

#include "ICollectionScreen.h"
#include "Menu/MainMenuScreen.h"
#include "Tetris/GameScreen.h"

namespace GameCollection
{
	typedef std::map<std::string, ICollectionScreen*> CollectionEntrys;
	
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
		 * Type: std::map<std::string, ICollectionEntry*>*
		 */
		static const CollectionEntrys* const getEntrys();

		/*
		 * Used to add a new module to GameCollection. The (first) screen of each module 
		 * needs to be set on startup. 
		 */
		static void addModuleEntrys(std::string modulName, ICollectionScreen* screen);
	};
}
