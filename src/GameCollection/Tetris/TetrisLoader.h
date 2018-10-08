#pragma once
#include "../Collection.h"
#include "../ICollectionEntry.h"
#include "TetrisMenu.h"
#include "SettingsMenu.h"
#include "Game.h"
#include "ScoreScreen.h"
#include <string>

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
		static std::map<SCREENS, GameCollection::ICollectionEntry*> s_modulScreens;

	public:
		TetrisLoader();
		~TetrisLoader();
		static void addScreen(SCREENS screenType, GameCollection::ICollectionEntry* screen);
		static GameCollection::ICollectionEntry** getScreen(SCREENS screenType);
		static Game* getGame();
		static bool contains(SCREENS screenType);
		static void erase(SCREENS screenType);
	};
}

