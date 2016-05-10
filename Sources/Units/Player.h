#pragma once

#include "SFML\Graphics.hpp"
#include "ShootingUnit.h"

using namespace sf;

//====================================================================================================

class Player : public ShootingUnit
{
public:
	struct Control
	{
		bool isUpPressed = false;
		bool isDownPressed = false;
		bool isLeftPressed = false;
		bool isRightPressed = false;
		bool isNabPressed = false;
		Vector2f cursorPosition = Vector2f(0.0F, 0.0F);
	};

	Player(RenderWindow& window,
		const Texture& texture,
		const Texture& bulletTexture,
		const Unit* parent = nullptr);
	virtual ~Player();

	virtual void update(float time) override;
	virtual void draw(float time) const override;
	void updateControl(const Control& control);

	virtual inline String CLASS_NAME() const override		{ return "Player"; }
	virtual inline float NORMAL_HEALTH() const override		{ return 100.0F; }
	virtual inline float NORMAL_DAMAGE() const override		{ return 25.0F; }
	virtual inline float NORMAL_SPEED() const override		{ return 300.0F; }
	virtual inline float NORMAL_COOLDOWN() const override	{ return 0.3F; }

protected:
	Control mControl;
};

