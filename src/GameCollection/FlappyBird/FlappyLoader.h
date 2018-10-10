#pragma once
#include "../Collection.h"
#include "FlappyMenuScreen.h"


namespace FlappyBirdGame {

class FlappyLoader {
public:
	static constexpr char MODUL_NAME[] = "FlappyBird";
	FlappyLoader() {
		GameCollection::Collection::addModuleEntrys(MODUL_NAME, new FlappyMenuScreen());;
	}
	virtual ~FlappyLoader() {};
};

} /* namespace FlappyBirdGame */
