#include "TransformComponent.h"

TransformComponent::TransformComponent(const glm::vec2& _position, const glm::vec2& _rotation, const glm::vec2& _scale) :
	m_position(_position),
	m_rotation(_rotation),
	m_scale(_scale)
{}

glm::vec2& TransformComponent::GetPosition()
{
	return m_position;
}

glm::vec2& TransformComponent::GetRotation()
{
	return m_rotation;
}

glm::vec2& TransformComponent::GetScale()
{
	return m_scale;
}

void TransformComponent::SetPosition(const glm::vec2& _position)
{
	m_position = _position;
}
