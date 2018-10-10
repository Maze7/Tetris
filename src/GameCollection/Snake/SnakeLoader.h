#pragma once
#include "../Collection.h"
#include "SnakeGame.h"

namespace SnakeGame {

	class SnakeLoader {
	public:
		static constexpr char MODUL_NAME[] = "Snake";

		SnakeLoader() {
			GameCollection::Collection::addModuleEntrys(MODUL_NAME, new SnakeGame());
		};
		virtual ~SnakeLoader() {};
	};
}


