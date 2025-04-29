#pragma once
#include "../Component.h"
#include <glm/glm.hpp>

class BallComponent : public Component
{
private:
		glm::vec2 m_initPos;
public:
	BallComponent();

	glm::vec2& GetInitPos();

};