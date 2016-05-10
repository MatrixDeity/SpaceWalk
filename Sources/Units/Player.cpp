#include "Player.h"

//====================================================================================================

Player::Player(RenderWindow& window, const Texture& texture, const Texture& bulletTexture, const Unit* parent) :
Unit(window, texture, parent),
ShootingUnit(window, texture, bulletTexture, parent),
mControl()
{
	mHealth = NORMAL_HEALTH();
	mDamage = NORMAL_DAMAGE();
	mSpeed = NORMAL_SPEED();
	mCooldown = NORMAL_COOLDOWN();

	mSprite.setTextureRect(IntRect(0, 0, 48, 32));
	mSprite.setOrigin(getBounds().width / 4.0F, getBounds().height / 4.0F);
}

//====================================================================================================

Player::~Player()
{
}

//====================================================================================================

void Player::update(float time)
{
	updateBullets(time);

	if (!mIsAlive)
		return;

	rotateTo(mControl.cursorPosition);
	float rotation = mSprite.getRotation();
	float sin = GameMath::sin(rotation);
	float cos = GameMath::cos(rotation);

	if (mControl.isUpPressed && !mControl.isDownPressed)
	{
		move(Vector2f(-mSpeed * cos * time, -mSpeed * sin * time));
		if (mControl.isLeftPressed && !mControl.isRightPressed)
			move(Vector2f(-mSpeed * sin * time, mSpeed * cos * time));
		if (mControl.isRightPressed && !mControl.isLeftPressed)
			move(Vector2f(mSpeed * sin * time, -mSpeed * cos * time));
	}
	else if (mControl.isDownPressed && !mControl.isUpPressed)
	{
		move(Vector2f(mSpeed * cos * time, mSpeed * sin * time));
		if (mControl.isLeftPressed && !mControl.isRightPressed)
			move(Vector2f(-mSpeed * sin * time, mSpeed * cos * time));
		if (mControl.isRightPressed && !mControl.isLeftPressed)
			move(Vector2f(mSpeed * sin * time, -mSpeed * cos * time));
	}

	if (mControl.isNabPressed)
		shoot();
}

//====================================================================================================

void Player::draw(float time) const
{
	drawBullets(time);

	drawSelf(time);
}

//====================================================================================================

void Player::updateControl(const Control& control)
{
	if (mControl.isUpPressed != control.isUpPressed)
		mControl.isUpPressed = control.isUpPressed;
	if (mControl.isDownPressed != control.isDownPressed)
		mControl.isDownPressed = control.isDownPressed;
	if (mControl.isLeftPressed != control.isLeftPressed)
		mControl.isLeftPressed = control.isLeftPressed;
	if (mControl.isRightPressed != control.isRightPressed)
		mControl.isRightPressed = control.isRightPressed;
	if (mControl.isNabPressed != control.isNabPressed)
		mControl.isNabPressed = control.isNabPressed;
	if (mControl.cursorPosition != control.cursorPosition)
		mControl.cursorPosition = control.cursorPosition;
}