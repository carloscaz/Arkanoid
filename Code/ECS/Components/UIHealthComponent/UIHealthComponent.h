#pragma once
#include "../Component.h"
//Player component to control the player in the game
class UIHealthComponent : public Component
{
	bool m_active;

public:
	UIHealthComponent();

	void SetActive(bool _value);
	bool GetActive() const;
};