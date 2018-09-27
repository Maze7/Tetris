#include "TetrisLoader.h"

constexpr char TetrisGame::TetrisLoader::MODUL_NAME[];

TetrisGame::TetrisLoader::TetrisLoader()
{
	GameCollection::Collection::addModuleEntrys(MODUL_NAME, &modulScreens);
}

/*
	
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
