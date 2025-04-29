#include "Colliders.h"

CircleCollider::CircleCollider(float _radius) :
	m_radius(_radius)
{
}

float CircleCollider::GetSize()
{
	return m_radius;
}

BoxCollider::BoxCollider() :
	m_size(glm::vec2(0))
{
}

BoxCollider::BoxCollider(const glm::vec2& _size) :
	m_size(_size)
{
}

glm::vec2& BoxCollider::GetSize()
{
	return m_size;
}
