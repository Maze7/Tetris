#pragma once
#include <SFML/Graphics.hpp>
#include "../ICollectionScreen.h"
#include "../Collection.h"
#include <string>

#include "GameScreen.h"
#include "MenuScreen.h"

namespace TetrisGame
{
	class SettingsScreen : public GameCollection::ICollectionScreen
	{
	private:
		/*
		 * Specify the menu entrys.
		 */
		enum ENTRYS {DIFFICULTY = 0, SOUND_VOLUME = 1, BACK = 2, END = 3 };
		const std::string entryNames[END] = {"Difficulty", "Sound Volume", "Back"};

		/*
		 * Specify the menu entry which is currently focused.
		 * On "startup" ist the first entry  (DIFFICULTY) focused
		 */
		ENTRYS m_hover = ENTRYS::DIFFICULTY;

		/*
		 * 0 = DEFAULT
		 * 1 = 5
		 * 2 = 10
		 * 3 = 15
		 */
		unsigned int m_difficulty = 0;

		/*
		 * m_difficulty * m_difficultyIntervall = the real start level
		 */
		const unsigned int m_difficultyIntervall = 5;

		unsigned int m_volume = 5;
		sf::Texture m_background;

	public:
		SettingsScreen();
		~SettingsScreen() {};

		void handleEvent(const sf::Event sfevent);
		void draw(sf::RenderWindow* window, sf::Font* font);
		int close(ICollectionScreen** screen);

		const unsigned int getDifficulty();
		float getSoundVolume();

	private:
		// helpers
		static constexpr int DIFFICULTY_SIZE = 4; // difficulty options
		static constexpr unsigned int MAX_VOLUME = 10;
	};
}
