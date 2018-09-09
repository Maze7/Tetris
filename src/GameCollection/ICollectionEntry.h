#pragma once
#include <SFML/Graphics.hpp>

namespace GameCollection
{
	/*
		Every entry/module in/for GameCollection like "Menu" or "Tetris" needs to implement this
		interface-like Class.

		> Common main-loop is 

		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
				else if (event.type == sf::Event::KeyPressed)
		!			collectionEntry.handleEvent(event);
			}
		!	collectionEntry.handleTime();
			window.clear();
		!	collectionEntry.draw(&window);
			window.display();
		}
	*/
	class ICollectionEntry
	{

	public:
		enum EXIT_CODE{ GOOD=0, ERROR=1 };

		/*
			-- PureVirtual -- 
			Every entry have to handle keyboard and/or mouse events. 
			It will called right before draw method.
		*/
		virtual void handleEvent(const sf::Event sfevent) = 0;
		
		/*
			This method will directly called after "handleEvent" outside the window.pollEvent loop.
			It should handle something like time/tick or other game behaviors. It will be called every
			loop right before the draw-method and before window.display(). There is no need to 
			override this method if its not needed (in a case like "Menu" entry, where is no need
			for any time/game behaviors).
		*/
		virtual void handleTime() {}
		
		/*
			--PureVirtual -- 
			Since this project is based on SFML, this method should draw every needed item/object 
			to the given window. This method will be called every frame right before displaying the window.
			The font and window are only available in this method. It should draw all the necessary components
			(like game objects or menu entries).

		*/
		virtual void draw(sf::RenderWindow* window, sf::Font* font) = 0;


		/*
		 *
		 */
		virtual int close() { return EXIT_CODE::GOOD; }

		/*
		 * Avoid compiler warning
		 */
		virtual ~ICollectionEntry() {};
	};
}

