#pragma once
#include <SFML/Graphics.hpp>

namespace GameCollection
{
	/*
	 *	Every screen which should be displayed, need to implement this inferface-like class. 
	 *	Each module can have multiple screens. See GameCollection::Collection. 
	 */
	class ICollectionEntry
	{
	protected:
		bool m_running = true;

	public:
		/*
		 * Pre-defined exit codes used in close(). 
		 */
		enum RETURN { MAIN_MENU = -1, EXIT_APP = -2 };

		/*
		 *	-- PureVirtual -- 
		 *	Every entry have to handle keyboard and/or mouse events. 
		 *	It will called right before draw method.
		 */
		virtual void handleEvent(const sf::Event sfevent) = 0;
		
		/*
		 *	This method will directly called after "handleEvent" outside the window.pollEvent loop.
		 *	It should handle something like time/tick or other game behaviors. It will be called every
		 *	loop right before the draw-method and before window.display(). There is no need to 
		 *	override this method if its not needed (in a case like "Menu" entry, where is no need
		 *	for any time/game behaviors).
		 */
		virtual void handleTime() {}
		
		/*
		 *	--PureVirtual -- 
		 *	Since this project is based on SFML, this method should draw every needed item/object 
		 *	to the given window. This method will be called every frame right before displaying the window.
		 *	The font and window are only available in this method. It should draw all the necessary components
		 *	(like game objects or menu entries).
 		 */
		virtual void draw(sf::RenderWindow* window, sf::Font* font) = 0;

		/*
		 * Close() will called if isRunning() is false. Its recommended to do some cleanup 
		 * like deleting pointers or something like this. 
		 * 
		 * The return value value specify what screen should displayed next. There are two 
		 * pre-defined return values which are located in RETURN-enum. 
		 * If close() returns MEIN_MENU the current ICollectionEntry wont displayed anymore and main menu will
		 * displayed again. EXIT_APP closes the hole window which will invoke the end of GameCollection. 
		 *
		 * Any other int value specify the next screen which will be shown inside the current screen/entry vector. 
		 * If close() returns 3 the Collection::s_screen.at(CURRENTMODUL)[3] will displayed next.
		 */
		virtual int close() { return MAIN_MENU; }

		/*
		 * Avoid compiler warning
		 */
		virtual ~ICollectionEntry() {};

		/*
		 * Specify if the current Entry/Screen/Module is running or not. Returns "m_running"
		 * The run/main method will call close() if isRunning() return false. It will called right after
		 * handleEvent() and before update() and draw()-
		 */
		virtual bool isRunning() { return m_running; }

		/*
		 * Sets m_running to true. It will prevent calling close() next loop. 
		 * It will called each time if the current screen will changed to another. 
		 */
		const virtual void setRunning() { m_running = true;  }
	};
}