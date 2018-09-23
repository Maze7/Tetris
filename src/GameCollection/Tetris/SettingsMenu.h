#pragma once
#include <SFML/Graphics.hpp>
#include "../ICollectionEntry.h"
#include "TetrisMenu.h"
#include "Game.h"
#include "../Collection.h"
#include <string>

namespace TetrisGame
{
	class SettingsMenu : public GameCollection::ICollectionEntry
	{
	private:
		/*
		 * Specify the menu entrys.
		 *
		 */
		enum ENTRYS { CONTINUE=0, DIFFICULTY = 1, SOUND_VOLUME = 2, BACK = 3, END = 4 };
		const std::string entryNames[END] = {"CONTINUE", "Difficulty", "Sound Volume", "Back"};
		ENTRYS m_currentState;

		/*
		 * Specify the menu entry which is currently focused.
		 * On "startup" ist the first entry  (DIFFICULTY) focused
		 */
		ENTRYS m_hover = ENTRYS::DIFFICULTY;

		unsigned int m_volume = 5;
		static constexpr unsigned int MAX_VOLUME = 10;

	public:
		SettingsMenu();
		~SettingsMenu() {};

		void handleEvent(const sf::Event sfevent);
		void draw(sf::RenderWindow* window, sf::Font* font);
		int close();
	};
}