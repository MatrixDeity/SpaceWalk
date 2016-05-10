#pragma once

#include "SFML\Graphics.hpp"
#include "GamePart.h"

using namespace sf;

//====================================================================================================

class GameState : public GamePart
{
public:
	GameState(RenderWindow& game);
	virtual ~GameState();

	virtual void handleInput() = 0;

protected:
	Event mEvent;
};

