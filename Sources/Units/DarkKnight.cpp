#include "DarkKnight.h"

//====================================================================================================

DarkKnight::DarkKnight(RenderWindow& window, const Texture& texture, const Texture& bulletTexture, Unit* target, const Unit* parent) :
Unit(window, texture, parent),
AiUnit(window, texture, target, parent),
ShootingUnit(window, texture, bulletTexture, parent)
{
	mHealth = NORMAL_HEALTH();
	mDamage = NORMAL_DAMAGE();
	mSpeed = NORMAL_SPEED();
	mCooldown = NORMAL_COOLDOWN();

	mSprite.setTextureRect(IntRect(0, 0, 48, 32));
	mSprite.setOrigin(getBounds().width / 4.0F, getBounds().height / 4.0F);
}

//====================================================================================================

DarkKnight::~DarkKnight()
{
}

//====================================================================================================

void DarkKnight::update(float time)
{
	updateBullets(time);

	if (!mIsAlive)
		return;

	decide(time);
}

//====================================================================================================

void DarkKnight::draw(float time) const
{
	drawBullets(time);
	
	if (!mIsVisible)
		return;

	drawSelf(time);
}

//====================================================================================================

void DarkKnight::decide(float time)
{
	if (mTarget == nullptr)
		return;

	const Vector2f& targetPosition = mTarget->getPosition();
	rotateTo(targetPosition);
	shoot();
	if (GameMath::computeDistance(mSprite.getPosition(), targetPosition) > ATTACK_DISTANCE())
		moveForward(time);
}