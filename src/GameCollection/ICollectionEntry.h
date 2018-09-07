#pragma once
#include <SFML/Graphics.hpp>

namespace GameCollection
{
	class ICollectionEntry
	{
	public:
		virtual void handleEvent(const sf::Event& sfevent) = 0;
		virtual void handleTime() {}
		virtual void draw(sf::RenderWindow& window) = 0;
	};
}

