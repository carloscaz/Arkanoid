#pragma once
#include <glm/glm.hpp>
#include "../ECS/Components/Component.h"

//Transform component with position, rotation and scale data
class TransformComponent : public Component
{
private:
	glm::vec2 m_position;
	glm::vec2 m_rotation;
	glm::vec2 m_scale;

public:
	TransformComponent() {};
	TransformComponent(const glm::vec2& _position, const glm::vec2& _rotation, const glm::vec2& _scale);

	glm::vec2& GetPosition();
	glm::vec2& GetRotation();
	glm::vec2& GetScale();

	void SetPosition(const glm::vec2& _position);
};