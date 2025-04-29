#pragma once
#include "../../Components/Component.h"

class BrickComponent : public Component
{
private:
	int m_lifes;
public:
	BrickComponent();
	BrickComponent(unsigned int _lifes);

	int GetLifes() const;
	void Hit();
};