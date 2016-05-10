#include "AiUnit.h"

//====================================================================================================

AiUnit::AiUnit(RenderWindow& window, const Texture& texture, Unit* target, const Unit* parent) :
Unit(window, texture, parent),
mTarget(target)
{
}

//====================================================================================================

AiUnit::~AiUnit()
{
}

//====================================================================================================

void AiUnit::setTarget(Unit* target)
{
	if (mTarget == target)
		return;

	mTarget = target;
}

//====================================================================================================

const Unit* AiUnit::getTarget() const
{
	return mTarget;
}

//====================================================================================================

void AiUnit::moveForward(float time)
{
	float rotation = mSprite.getRotation();
	float sin = GameMath::sin(rotation);
	float cos = GameMath::cos(rotation);
	move(Vector2f(-mSpeed * cos * time, -mSpeed * sin * time));
}