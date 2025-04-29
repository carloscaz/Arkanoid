#pragma once
#include "../Component.h"

class PowerUpComponent : public Component
{
private:
	bool m_catched;
public:
	PowerUpComponent();
	virtual ~PowerUpComponent();

	void SetCatched(bool _value);

	bool GetCatched() const;
};

class AddBallPowerUpComponent : public PowerUpComponent
{
public:
	AddBallPowerUpComponent();
};

class AccelerateBallPowerUp : public PowerUpComponent
{
public:
	AccelerateBallPowerUp();
};

class DecelerateBallPowerUp : public PowerUpComponent
{
public:
	DecelerateBallPowerUp();
};