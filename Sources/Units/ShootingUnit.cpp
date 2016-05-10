#include "ShootingUnit.h"

//====================================================================================================

ShootingUnit::ShootingUnit(RenderWindow& window, const Texture& texture, const Texture& bulletTexture, const Unit* parent) :
Unit(window, texture, parent),
mBulletTexture(bulletTexture),
mBullets(),
mCooldownTimer(),
mCooldown(0.0F)
{
}

//====================================================================================================

ShootingUnit::~ShootingUnit()
{
}

//====================================================================================================

void ShootingUnit::updateBullets(float time)
{
	for (auto it = mBullets.begin(); it != mBullets.end();)
		if ((*it)->isAlive())
		{
			(*it)->update(time);
			++it;
		}
		else
			it = mBullets.erase(it);
}

//====================================================================================================

void ShootingUnit::drawBullets(float time) const
{
	for (const auto& bullet : mBullets)
		bullet->draw(time);
}

//====================================================================================================

void ShootingUnit::shoot()
{
	if (mCooldownTimer.getElapsedTime().asSeconds() < mCooldown)
		return;

	mBullets.push_back(std::make_shared<Bullet>(mWindow, mBulletTexture, this));
	mCooldownTimer.restart();
}

//====================================================================================================

void ShootingUnit::setCooldown(float cooldown)
{
	if (mCooldown == cooldown)
		return;

	mCooldown = cooldown > 0.0F ? cooldown : 0.0F;
}

//====================================================================================================

const std::list<std::shared_ptr<Bullet>>& ShootingUnit::getAllBullets() const
{
	return mBullets;
}

//====================================================================================================

bool ShootingUnit::hasBullets() const
{
	return !mBullets.empty();
}

//====================================================================================================

float ShootingUnit::getCooldown() const
{
	return mCooldown;
}