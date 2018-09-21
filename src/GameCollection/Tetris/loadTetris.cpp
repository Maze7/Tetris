#include "../ICollectionEntry.h"
#include "../Collection.h"
#include "TetrisMenu.h"
#include "Game.h"

namespace TetrisGame
{
	namespace // anonymous namespace
	{
		struct TetrisLoader
		{
			TetrisGame::Game TetrisGame = TetrisGame::Game();
			TetrisGame::TetrisMenu TetrisMenu = TetrisGame::TetrisMenu();
			std::vector<GameCollection::ICollectionEntry*> tetrisEntrys;

			TetrisLoader()
			{
				tetrisEntrys.push_back(&TetrisMenu);
				tetrisEntrys.push_back(&TetrisGame);
				GameCollection::Collection::addModuleEntrys("Tetris", &tetrisEntrys);
			}
		};
		static TetrisLoader load; // invoke struct and lode Tetris into GameCollection::Collection
	}
}