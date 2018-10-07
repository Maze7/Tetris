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
		/*
			This is the module vector for tetris. It Contains all Screens which will used in this module. 
			There can be objects and nullptr. 
			Use nullptr to reserve the space affliate to SCREENS.
			Initialize a object if it needs at startup. 
		*/
		std::vector<GameCollection::ICollectionEntry*> modulScreens = { new TetrisMenu()/*0*/, nullptr/*1*/ , nullptr/*2*/, nullptr/*3*/};

	public:

		static constexpr char MODUL_NAME[] = "Tetris";
		/*
			
		*/
		enum SCREENS { MENU=0, GAME=1, SETTINGS=2, SCORE=3 };

		TetrisLoader() { GameCollection::Collection::addModuleEntrys(MODUL_NAME, &modulScreens); }
	};
}

// allocate memory
constexpr char TetrisGame::TetrisLoader::MODUL_NAME[];

/*
	Loads the TetrisModule in a private/anonymous namespace
	It invokes the Loader where the class TetrisLoader will be initialized
*/
namespace
{
	using namespace TetrisGame;
	struct Loader
	{
		static const TetrisLoader loading;
	};
	const TetrisLoader Loader::loading = TetrisLoader();
}
