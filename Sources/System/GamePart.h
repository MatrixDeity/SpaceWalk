#pragma once

#include "SFML\Graphics.hpp"

using namespace sf;

//====================================================================================================

class GamePart
{
public:
	GamePart(RenderWindow& window);
	virtual ~GamePart();

	virtual void update(float time) = 0;
	virtual void draw(float time) const = 0;

	virtual inline String CLASS_NAME() const { return "GamePart"; }

protected:
	RenderWindow& mWindow;
};

