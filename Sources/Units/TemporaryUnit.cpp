#include "TemporaryUnit.h"

//====================================================================================================

TemporaryUnit::TemporaryUnit(RenderWindow& window, const Texture& texture, const Unit* parent) :
Unit(window, texture, parent),
mLifetime(0.0F)
{
}

//====================================================================================================

TemporaryUnit::~TemporaryUnit()
{
}

//====================================================================================================

void TemporaryUnit::spendLifetime(float lifetime)
{
	if (!mIsAlive)
		return;

	mLifetime -= lifetime;
	if (mLifetime <= 0.0F)
	{
		mLifetime = 0.0F;
		kill();
	}
	else if (mLifetime > NORMAL_LIFETIME())
		mLifetime = NORMAL_LIFETIME();
}

//====================================================================================================

void TemporaryUnit::setLifetime(float lifetime)
{
	if (mLifetime == lifetime)
		return;

	if (lifetime > 0.0F)
		mLifetime = lifetime;
	else
		kill();
}

//====================================================================================================

float TemporaryUnit::getLifetime() const
{
	return mLifetime;
}