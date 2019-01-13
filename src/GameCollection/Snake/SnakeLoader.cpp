#include "SnakeLoader.h"

namespace SnakeGame {

constexpr char SnakeLoader::MODUL_NAME[];
/*
	Loads the SnakeModule in a private/anonymous namespace
	It invokes the Loader where the class SnakeLoader will be initialized
*/
namespace {
	struct Loader {
		static const SnakeLoader loading;
	};
	const SnakeLoader Loader::loading = SnakeLoader();
} /* namespace anonymous */

} /* namespace SnakeGame */