#pragma once
#include <glm/glm.hpp>

class Vertex
{
public:
	glm::vec2 m_position; //Vertex position
	glm::vec2 m_tex; ////Vertex texture coord

	Vertex(const glm::vec2& _position, const glm::vec2& _tex);
};