#pragma once
#include <SFML/Graphics.hpp>

namespace GameCollection
{
	/*
	 *	Every screen which should be displayed, need to implement this inferface-like class. 
	 *	Each module can have multiple screens. See GameCollection::Collection. 
	 */
	class ICollectionScreen
	{
	protected:
		bool m_running = true;

	public:
		/*
		 * Pre-defined exit codes used in close().
		 * MAIN_MENU will set the current screen pointer to the main menu
		 * CONTINUE will set m_running of screen pointer to true (normally used if the close method changed the screen pointer)
		 * EXIT_APP will exit the application with return code success
		 */
		enum RETURN { MAIN_MENU = -1, EXIT_APP = EXIT_SUCCESS, CONTINUE = -3 };

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
		virtual void update() {}
		
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
		 * The parameter screen is the current ICollectionEntry which is inside the run-loop. 
		 * You can let the pointer (*screen) point to another ICollectionEntry if needed. 
		 * This method can controll which Entryscreen should displayed next (modify *screen
		 * 
		 * The return int decides what happens with the running instance of Collection. 
		 * This method should return an exit code or one of the pre-defined RETURN enums
		 * In case *screen is nullptr the application will exit immediately.
		 * 
		 */
		virtual int close(ICollectionScreen** screen) { return EXIT_SUCCESS; }

		/*
		 * Avoid compiler warning
		 */
		virtual ~ICollectionScreen() {};

		/*
		 * Specify if the current Entry/Screen/Module is running or not. Returns "m_running"
		 * The run/main method will call close() if isRunning() return false. It will called right after
		 * handleEvent() and before update() and draw()-
		 */
		virtual bool isRunning() { return m_running; }

		/*
		 * Sets m_running to true. It will prevent calling close() next loop. 
		 * It will called each time if the current screen will changed to another. 
		 * ( m_running = true; if the current ICollectionEntry pointer is not nullptr )
		 */
		const virtual void setRunning() { m_running = true;  }
	};
}