#include "SnakeLoader.h"

constexpr char SnakeGame::SnakeLoader::MODUL_NAME[];
	/*
		Loads the SnakeModule in a private/anonymous namespace
		It invokes the Loader where the class SnakeLoader will be initialized
	*/
	namespace {
		using namespace SnakeGame;
		struct Loader {
			static const SnakeLoader loading;
		};
		const SnakeLoader Loader::loading = SnakeLoader();
	}
