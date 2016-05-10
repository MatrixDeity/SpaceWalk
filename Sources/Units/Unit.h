#pragma once

#include <map>

#include "SFML\Graphics.hpp"
#include "AnimatedSprite.h"
#include "GamePart.h"
#include "GameMath.h"

using namespace sf;

//====================================================================================================

class Unit : public GamePart
{
public:
	Unit(RenderWindow& window,
		const Texture& texture,
		const Unit* parent = nullptr);
	virtual ~Unit();

	virtual bool intersects(const Unit* unit) const;

	void move(const Vector2f& offset);
	void rotate(float angle);
	void rotateTo(const Vector2f& point);
	void scale(const Vector2f& factor);
	void blur(Uint8 blackout, Uint8 transparency = 0U);
	void kill();
	void causeDamage(float damage);

	void setPosition(const Vector2f& position);
	void setRotation(float angle);
	void setScale(const Vector2f& scale);
	void setColor(const Color& color);
	void setVisible(bool visible);
	void setHealth(float health);
	void setDamage(float damage);
	void setSpeed(float speed);

	static const std::map<Uint32, Unit*>& getAllUnits();
	Uint32 getId() const;
	const Vector2f& getPosition() const;
	float getRotation() const;
	const Vector2f& getScale() const;
	const Color& getColor() const;
	const FloatRect& getBounds() const;
	bool isVisible() const;
	bool isAlive() const;
	float getHealth() const;
	float getDamage() const;
	float getSpeed() const;

	virtual inline String CLASS_NAME() const override	{ return "Unit"; }
	virtual inline float NORMAL_HEALTH() const = 0;
	virtual inline float NORMAL_DAMAGE() const = 0;
	virtual inline float NORMAL_SPEED() const = 0;

protected:
	void drawSelf(float time) const;

	AnimatedSprite mSprite;
	const Unit* mParent;
	const Uint32 mId;
	bool mIsAlive;
	bool mIsVisible;
	float mHealth;
	float mDamage;
	float mSpeed;

	static std::map<Uint32, Unit*> mUnits;
	static Uint32 mNextId;
	static const Uint32 MAX_ID;
};

