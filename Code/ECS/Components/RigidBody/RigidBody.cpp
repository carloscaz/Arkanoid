#include "RigidBody.h"

RigidBody::RigidBody() :
	m_velocity(glm::vec2(0))
{}

RigidBody::RigidBody(const glm::vec2 & _velocity) :
	m_velocity(_velocity)
{}

void RigidBody::SetVelocity(const glm::vec2 & _velocity)
{
	m_velocity = _velocity;
}

glm::vec2& RigidBody::GetVelocity()
{
	return m_velocity;
}
