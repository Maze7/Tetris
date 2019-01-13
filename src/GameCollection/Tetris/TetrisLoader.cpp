#include "TetrisLoader.h"

namespace TetrisGame {

// allocate memory (static elements)
constexpr char TetrisLoader::MODUL_NAME[];
std::map <TetrisLoader::SCREENS, GameCollection::ICollectionScreen*> TetrisLoader::s_modulScreens;

TetrisLoader::TetrisLoader() { 
	TetrisLoader::s_modulScreens.insert(std::make_pair(MENU, new MenuScreen()));
	GameCollection::Collection::addModuleEntrys(MODUL_NAME, s_modulScreens.at(MENU)); 
}

TetrisLoader::~TetrisLoader() {
	for (auto screen : TetrisLoader::s_modulScreens) {
		if( screen.first != MENU) // menu is inside vector in Collection-class. It will deleted there
			delete screen.second;
	}
}

/*
	Params:
		SCREENS the type of the module
		ICollectionEntry* screen to add
*/
void TetrisLoader::addScreen(TetrisLoader::SCREENS screenType, GameCollection::ICollectionScreen* screen) {
	s_modulScreens.insert(std::make_pair(screenType, screen));
}

/*
	Returns a pointer to ICollectionEntry* out of the map s_modulScreens. 
	Param: 
		SCREENS defines which ICollectionEntry will return

	Example Usage:
		Game* game = dynamic_cast<Game*>(TetrisLoader::getScreen(TetrisLoader::GAME)); // with dynamic cast

*/
GameCollection::ICollectionScreen** TetrisLoader::getScreen(TetrisLoader::SCREENS screenType) {
	return &s_modulScreens.at(screenType);
}

GameScreen* TetrisLoader::getGame() {
	if (TetrisLoader::contains(GAME)) {
		return dynamic_cast<GameScreen*>(*TetrisLoader::getScreen(GAME));
	} else {
		return nullptr;
	}
}

bool TetrisLoader::contains(TetrisLoader::SCREENS screenType) {
	return s_modulScreens.count(screenType); // will count the number of screenType in this map
											 // If >1 items exist this value will returned (everything >0 is true)
}

/*
	This method will free the memory and erase the pointer out of s_modulScreens. 
	If the screen doesnt exist, this method will do nothing
	Param:
		SCREENS - which entry of s_modulScreen should erased.
*/
void TetrisLoader::erase(TetrisLoader::SCREENS screenType) {
	if (TetrisLoader::contains(screenType)) {
		delete s_modulScreens.at(screenType);
		s_modulScreens.erase(screenType);
	}
}

/*
	Loads the TetrisModule in a private/anonymous namespace
	It invokes the Loader where the class TetrisLoader will be initialized
*/
namespace {

struct Loader {
	static const TetrisLoader loading;
};
const TetrisLoader Loader::loading = TetrisLoader();

} /* namespace anonymous */

} /* namespace TetrisGame */