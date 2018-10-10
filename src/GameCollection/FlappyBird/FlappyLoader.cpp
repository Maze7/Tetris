#include "FlappyLoader.h"

constexpr char FlappyBirdGame::FlappyLoader::MODUL_NAME[];

namespace {
using namespace FlappyBirdGame;
struct Loader {
	static const FlappyLoader loading;
};
const FlappyLoader Loader::loading = FlappyLoader();

} /* namespace anonymous */
