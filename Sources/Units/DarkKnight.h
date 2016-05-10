#pragma once

#include "SFML\Graphics.hpp"
#include "AiUnit.h"
#include "ShootingUnit.h"
#include "GameMath.h"

using namespace sf;

//====================================================================================================

class DarkKnight : public AiUnit, public ShootingUnit
{
public:
	DarkKnight(RenderWindow& window,
		const Texture& texture,
		const Texture& bulletTexture,
		Unit* target = nullptr,
		const Unit* parent = nullptr);
	virtual ~DarkKnight();

	virtual void update(float time) override;
	virtual void draw(float time) const override;

	virtual inline String CLASS_NAME() const override		{ return "DarkKnight"; }
	virtual inline float NORMAL_HEALTH() const				{ return 50.0F; };
	virtual inline float NORMAL_DAMAGE() const				{ return 25.0F; };;
	virtual inline float NORMAL_SPEED() const				{ return 150.0F; };
	virtual inline float NORMAL_COOLDOWN() const			{ return 2.0F; };
	virtual inline float ATTACK_DISTANCE() const override	{ return 400.0F; }

protected:
	virtual void decide(float time) override;
};

