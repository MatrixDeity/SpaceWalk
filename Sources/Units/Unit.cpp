#include "Unit.h"

//====================================================================================================

std::map<Uint32, Unit*> Unit::mUnits;
Uint32 Unit::mNextId = 0;
const Uint32 Unit::MAX_ID = 0xFFFFFFFF;

//====================================================================================================

Unit::Unit(RenderWindow& window, const Texture& texture, const Unit* parent) :
GamePart(window),
mSprite(texture),
mParent(parent),
mId(mNextId),
mIsVisible(true),
mIsAlive(true),
mHealth(0.0F),
mDamage(0.0F),
mSpeed(0.0F)
{
	mUnits[mId] = this;
	++mNextId %= MAX_ID;
	mSprite.setOrigin(getBounds().width / 2.0F, getBounds().height / 2.0F);
	setScale(Vector2f(2.0F, 2.0F));
	if (parent)
	{
		setPosition(parent->getPosition());
		setRotation(parent->getRotation());
	}
	else
	{
		setPosition(Vector2f(0.0F, 0.0F));
		setRotation(0.0F);
	}
}

//====================================================================================================

Unit::~Unit()
{
	mUnits.erase(mId);
}

//====================================================================================================

bool Unit::intersects(const Unit* unit) const
{
	return getBounds().intersects(unit->getBounds());
}

//====================================================================================================

void Unit::move(const Vector2f& offset)
{
	mSprite.move(offset);
}

//====================================================================================================

void Unit::rotate(float angle)
{
	mSprite.rotate(angle);
}

//====================================================================================================

void Unit::rotateTo(const Vector2f& point)
{
	const Vector2f& position = mSprite.getPosition();
	mSprite.setRotation(GameMath::atan2(position.y - point.y, position.x - point.x));
}

//====================================================================================================

void Unit::scale(const Vector2f& factor)
{
	mSprite.scale(factor);
}

//====================================================================================================

void Unit::blur(Uint8 blackout, Uint8 transparency)
{
	// Needs a implementation!
}

//====================================================================================================

void Unit::kill()
{
	if (!mIsAlive)
		return;

	mIsAlive = false;
	if (mHealth != 0.0F)
		mHealth = 0.0F;
}

//====================================================================================================

void Unit::causeDamage(float damage)
{
	if (!mIsAlive)
		return;

	mHealth -= damage;
	if (mHealth <= 0.0F)
		kill();
	else if (mHealth > NORMAL_HEALTH())
		mHealth = NORMAL_HEALTH();
}

//====================================================================================================

void Unit::setPosition(const Vector2f& position)
{
	mSprite.setPosition(position);
}

//====================================================================================================

void Unit::setRotation(float angle)
{
	mSprite.setRotation(angle);
}

//====================================================================================================

void Unit::setScale(const Vector2f& scale)
{
	mSprite.setScale(scale);
}

//====================================================================================================

void Unit::setColor(const Color& color)
{
	mSprite.setColor(color);
}

//====================================================================================================

void Unit::setVisible(bool visible)
{
	if (mIsVisible == visible)
		return;

	mIsVisible = visible;
}

//====================================================================================================

void Unit::setHealth(float health)
{
	if (mHealth == health)
		return;
	
	if (health > 0.0F)
		mHealth = health;
	else
		kill();
}

//====================================================================================================

void Unit::setDamage(float damage)
{
	if (mDamage == damage)
		return;

	mDamage = damage > 0.0F ? damage : 0.0F;
}

//====================================================================================================

void Unit::setSpeed(float speed)
{
	if (mSpeed == speed)
		return;

	mSpeed = speed > 0.0F ? speed : 0.0F;
}

//====================================================================================================

const std::map<Uint32, Unit*>& Unit::getAllUnits()
{
	return mUnits;
}

//====================================================================================================

Uint32 Unit::getId() const
{
	return mId;
}

//====================================================================================================

const Vector2f& Unit::getPosition() const
{
	return mSprite.getPosition();
}

//====================================================================================================

float Unit::getRotation() const
{
	return mSprite.getRotation();
}

//====================================================================================================

const Vector2f& Unit::getScale() const
{
	return mSprite.getScale();
}

//====================================================================================================

const Color& Unit::getColor() const
{
	return mSprite.getColor();
}

//====================================================================================================

const FloatRect& Unit::getBounds() const
{
	return mSprite.getGlobalBounds();
}

//====================================================================================================

bool Unit::isAlive() const
{
	return mIsAlive;
}

//====================================================================================================

float Unit::getHealth() const
{
	return mHealth;
}

//====================================================================================================

float Unit::getDamage() const
{
	return mDamage;
}

//====================================================================================================

float Unit::getSpeed() const
{
	return mSpeed;
}

//====================================================================================================

void Unit::drawSelf(float time) const
{
	if (!mIsVisible)
		return;

	mWindow.draw(mSprite);
}