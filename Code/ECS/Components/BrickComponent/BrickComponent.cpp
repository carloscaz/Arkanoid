#include "BrickComponent.h"

BrickComponent::BrickComponent() :
	m_lifes(3)
{
}

BrickComponent::BrickComponent(unsigned int _lifes) :
	m_lifes(_lifes)
{
}

int BrickComponent::GetLifes() const
{
	return m_lifes;
}

void BrickComponent::Hit()
{
	if (m_lifes >= 0)
	{
		m_lifes--;
	}
}
