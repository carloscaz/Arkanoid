#include "PlayerComponent.h"
#include <iostream>

PlayerComponent::PlayerComponent() :
	m_active(true)
{
}

PlayerComponent::PlayerComponent(float _velocity) :
	m_playerVelocity(_velocity),
	m_score(0),
	m_lifes(3),
	m_active(true)
{}

void PlayerComponent::SetActive(bool _value)
{
	m_active = _value;
}

bool PlayerComponent::GetActive() const
{
	return m_active;
}

float PlayerComponent::GetPlayerVelocity()
{
	return m_playerVelocity;
}

unsigned int PlayerComponent::GetPlayerLifes()
{
	return m_lifes;
}

unsigned int PlayerComponent::GetPlayerScore()
{
	return m_score;
}

void PlayerComponent::IncreaseScore()
{
	m_score += 100;
	std::cout << m_score << std::endl;
}

void PlayerComponent::ResetScore()
{
	m_score = 0;
	std::cout << m_score << std::endl;
}

void PlayerComponent::ReduceLife()
{
	if (m_lifes > 0)
	{
		m_lifes--;
	}
}
