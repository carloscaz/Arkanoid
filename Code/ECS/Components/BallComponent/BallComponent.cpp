#include "BallComponent.h"

BallComponent::BallComponent() :
	m_initPos(glm::vec2(400,200))
{
}

glm::vec2& BallComponent::GetInitPos()
{
	return m_initPos;
}
