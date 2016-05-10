#pragma once

#include <list>
#include <memory>

#include "SFML\Graphics.hpp"
#include "ResourcesManager.h"
#include "GameMath.h"
#include "Unit.h"
#include "Bullet.h"

using namespace sf;

//====================================================================================================

class ShootingUnit : virtual public Unit
{
public:
	ShootingUnit(RenderWindow& window,
		const Texture& texture,
		const Texture& bulletTexture,
		const Unit* parent = nullptr);
	virtual ~ShootingUnit();

	void setCooldown(float cooldown);

	const std::list<std::shared_ptr<Bullet>>& getAllBullets() const;
	bool hasBullets() const;
	float getCooldown() const;

	virtual inline String CLASS_NAME() const override	{ return "ShootingUnit"; }
	virtual inline float NORMAL_COOLDOWN() const = 0;

protected:
	void updateBullets(float time);
	void drawBullets(float time) const;
	void shoot();

	const Texture& mBulletTexture;
	std::list<std::shared_ptr<Bullet>> mBullets;
	Clock mCooldownTimer;
	float mCooldown;
};

