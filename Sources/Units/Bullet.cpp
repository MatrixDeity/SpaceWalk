#include "Bullet.h"
#include <iostream>

//====================================================================================================

Bullet::Bullet(RenderWindow& window, const Texture& texture, const Unit* parent) :
Unit(window, texture, parent),
TemporaryUnit(window, texture, parent),
OFFSET_X(-NORMAL_SPEED() * GameMath::cos(getRotation())),
OFFSET_Y(-NORMAL_SPEED() * GameMath::sin(getRotation()))
{
	mHealth = NORMAL_HEALTH();
	mDamage = NORMAL_DAMAGE();
	mSpeed = NORMAL_SPEED();
	mLifetime = NORMAL_LIFETIME();
}

//====================================================================================================

Bullet::~Bullet()
{
}

//====================================================================================================

void Bullet::update(float time)
{
	if (!mIsAlive)
		return;

	move(Vector2f(OFFSET_X * time, OFFSET_Y * time));
	for (auto& pair : mUnits)
		if (pair.first != mId && pair.first != mParent->getId() && GameMath::computeDistance(getPosition(), pair.second->getPosition()) < 30.0F)
		{
			//std::cout << getBounds().height << ' ' << getBounds().width << std::endl;
			pair.second->causeDamage(mParent->getDamage());
			kill();
		}
	spendLifetime(time);
}

//====================================================================================================

void Bullet::draw(float time) const
{
	drawSelf(time);
}