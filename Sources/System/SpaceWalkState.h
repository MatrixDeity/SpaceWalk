#pragma once

#include <memory>
#include <list>

#include "SFML\Graphics.hpp"
#include "GameMath.h"
#include "GameState.h"
#include "ResourcesManager.h"
#include "Player.h"
#include "DarkKnight.h"

using namespace sf;

//====================================================================================================

class SpaceWalkState : public GameState
{
public:
	SpaceWalkState(RenderWindow& game);
	virtual ~SpaceWalkState();

	virtual void update(float time) override;
	virtual void draw(float time) const override;
	virtual void handleInput() override;

protected:
	Player mPlayer;
	Player::Control mControl;
	std::list<std::shared_ptr<Unit>> mEnemies;
	Sprite mEmblem;
	Sprite mBackground;
	View mCamera;
	View mPanel;
};

