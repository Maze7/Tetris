#pragma once
#include "../Collection.h"
#include "FlappyBirdScreen.h"


namespace FlappyBirdGame {

class FlappyLoader {
public:
	static constexpr char MODUL_NAME[] = "FlappyBird";
	FlappyLoader() {
		GameCollection::Collection::addModuleEntrys(MODUL_NAME, new FlappyBirdScreen());;
	}
	virtual ~FlappyLoader() {};
};

} /* namespace FlappyBirdGame */
