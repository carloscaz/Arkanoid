#pragma once
#include <glm/glm.hpp>
#include "../Component.h"

//Collider component base class
class Collider : public Component
{
public:
	virtual ~Collider() = default;
};

//Circle collider component
class CircleCollider : public Collider
{
private:
	float m_radius;

public:
	CircleCollider() : m_radius(0.0f) {};
	CircleCollider(float _radius);

	float GetSize();
};

//Box collider component
class BoxCollider : public Collider
{
private:
	glm::vec2 m_size;

public:
	BoxCollider();
	BoxCollider(const glm::vec2& _size);

	glm::vec2& GetSize();
};