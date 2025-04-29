#pragma once
#include "../Vertex/Vertex.h"

#include <vector>
//Buffer class with vectors of the vetices and indices to render in OpenGL
class Buffer2D
{
private:
	unsigned int m_VBO, m_VAO, m_EBO;

public:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	Buffer2D();

	void Draw();
};

class TextBuffer
{
private:
	unsigned int m_VBO, m_VAO, m_EBO;

public:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	TextBuffer();

	void Draw();
};