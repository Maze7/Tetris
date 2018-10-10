#include "FlappyLoader.h"

namespace {
using namespace FlappyBirdGame;
struct Loader {
	static const FlappyLoader loading;
};
const FlappyLoader Loader::loading = FlappyLoader();

} /* namespace anonymous */
