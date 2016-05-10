#pragma once

#include "SFML\Graphics.hpp"
#include "TemporaryUnit.h"
#include "GameMath.h"

using namespace sf;

//====================================================================================================

class Bullet : public TemporaryUnit
{
public:
	Bullet(RenderWindow& window,
		const Texture& texture,
		const Unit* parent = nullptr);
	virtual ~Bullet();

	virtual void update(float time) override;
	virtual void draw(float time) const override;

	virtual inline String CLASS_NAME() const override		{ return "Bullet"; }
	virtual inline float NORMAL_HEALTH() const override		{ return 1.0F; }
	virtual inline float NORMAL_DAMAGE() const override		{ return 0.0F; }
	virtual inline float NORMAL_SPEED() const override		{ return 1e3F; }
	virtual inline float NORMAL_LIFETIME() const override	{ return 1.5F; }

protected:
	const float OFFSET_X;
	const float OFFSET_Y;
};

