#pragma once
#include <glm/glm.hpp>
#include "../Component.h"

//RigidBody component with velocity and acceleration data
class RigidBody : public Component
{
private:
	glm::vec2 m_velocity;

public:
	RigidBody();
	RigidBody(const glm::vec2& _velocity);

	void SetVelocity(const glm::vec2& _velocity);

	glm::vec2& GetVelocity();
};