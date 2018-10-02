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
	private:
		Game game = Game();
		TetrisMenu menu = TetrisMenu();
		SettingsMenu settings = SettingsMenu();
		ScoreScreen score = ScoreScreen();

		std::vector<GameCollection::ICollectionEntry*> modulScreens = {&menu/*0*/, &game/*1*/ , &settings/*2*/, &score/*3*/};
	public:
		static constexpr char MODUL_NAME[] = "Tetris";
		enum SCREENS { MENU=0, GAME=1, SETTINGS=2, SCORE=3};

		TetrisLoader();
	};
}