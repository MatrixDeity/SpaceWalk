#pragma once

#include "Unit.h"

using namespace sf;

//====================================================================================================

class AiUnit : virtual public Unit
{
public:
	AiUnit(RenderWindow& window,
		const Texture& texture,
		Unit* target = nullptr,
		const Unit* parent = nullptr);
	virtual ~AiUnit();

	void setTarget(Unit* target);

	const Unit* getTarget() const;

	virtual inline String CLASS_NAME() const override		{ return "AiUnit"; }
	virtual inline float ATTACK_DISTANCE() const = 0;

protected:
	virtual void decide(float time) = 0;
	void moveForward(float time);

	Unit* mTarget;
};

