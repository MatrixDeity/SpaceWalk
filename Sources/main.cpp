#include <memory>

#include "SFML/Graphics.hpp"
#include "Game.h"
#include "SpaceWalkState.h"

using namespace sf;

//====================================================================================================

int main()
{
	Game game;
	game.pushState(std::make_shared<SpaceWalkState>(game.getWindow()));
	game.run();

    return 0;
}