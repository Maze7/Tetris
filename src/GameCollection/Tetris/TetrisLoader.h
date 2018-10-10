#pragma once
#include "../Collection.h"
#include "../ICollectionScreen.h"
#include "ScoreScreen.h"
#include <string>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingsScreen.h"

namespace TetrisGame
{
	class TetrisLoader
	{
	public:
		enum SCREENS { MENU = 0, GAME = 1, SETTINGS = 2, SCORE = 3 };
		static constexpr char MODUL_NAME[] = "Tetris";
	
	private:
		/*
		 * This map keeps all ICollectionEntrys which needs in Tetris
		 * Add entrys during runtime with addScreen(SCREENS, ICollectionEntry*)
		 * Get them with the relevant getter (game etc).
		 */
		static std::map<SCREENS, GameCollection::ICollectionScreen*> s_modulScreens;

	public:
		TetrisLoader();
		~TetrisLoader();
		static void addScreen(SCREENS screenType, GameCollection::ICollectionScreen* screen);
		static GameCollection::ICollectionScreen** getScreen(SCREENS screenType);
		static GameScreen* getGame();
		static bool contains(SCREENS screenType);
		static void erase(SCREENS screenType);
	};
}

