#include "PowerUpComponent.h"

PowerUpComponent::PowerUpComponent() :
	m_catched(false)
{
}

PowerUpComponent::~PowerUpComponent()
{
}

void PowerUpComponent::SetCatched(bool _value)
{
	m_catched = _value;
}

bool PowerUpComponent::GetCatched() const
{
	return m_catched;
}

AddBallPowerUpComponent::AddBallPowerUpComponent()
{
}

AccelerateBallPowerUp::AccelerateBallPowerUp()
{
}

DecelerateBallPowerUp::DecelerateBallPowerUp()
{
}
