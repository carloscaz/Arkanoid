#pragma once
#include "../Component.h"
#include <glm/glm.hpp>

//Player component to control the player in the game
class PlayerComponent : public Component
{
	bool m_active;

	float m_playerVelocity;
	unsigned int m_score;
	unsigned int m_lifes;

public:
	PlayerComponent();
	PlayerComponent(float _velocity);

	void SetActive(bool _value);
	bool GetActive() const;

	float GetPlayerVelocity();
	unsigned int GetPlayerLifes();
	unsigned int GetPlayerScore();

	void IncreaseScore();
	void ResetScore();


	void ReduceLife();
};