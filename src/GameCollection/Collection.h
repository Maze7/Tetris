#pragma once
#include <SFML/Graphics.hpp>
#include "Tetris/Game.h"
#include "ICollectionEntry.h"
#include "Menu/MenuEntry.h"

namespace GameCollection
{
	typedef std::map<std::string, std::vector<ICollectionEntry*>*> CollectionEntrys;
	
	class Collection
	{
	private:
		static CollectionEntrys s_entrys;

	public:
		Collection() {};
		~Collection() {};

		int run(sf::RenderWindow& window, sf::Font& font);
		void checkScreenStatus(ICollectionEntry** screen);

		static const CollectionEntrys* const getEntrys();
		static void addModuleEntrys(std::string modulName, std::vector<ICollectionEntry*>* screens);
	};
}