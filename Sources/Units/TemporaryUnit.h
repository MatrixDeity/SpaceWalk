#pragma once

#include "SFML\Graphics.hpp"
#include "Unit.h"

using namespace sf;

//====================================================================================================

class TemporaryUnit : virtual public Unit
{
public:
	TemporaryUnit(RenderWindow& window,
		const Texture& texture,
		const Unit* parent = nullptr);
	virtual ~TemporaryUnit();

	void spendLifetime(float lifetime);

	void setLifetime(float lifetime);

	float getLifetime() const;

	virtual inline String CLASS_NAME() const override	{ return "TemporaryUnit"; }
	virtual inline float NORMAL_LIFETIME() const = 0;

protected:
	float mLifetime;
};

