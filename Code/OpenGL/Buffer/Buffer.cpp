#include "Buffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Vertex/Vertex.h"
#include <iostream>

Buffer2D::Buffer2D()
{
	//Default vertex vector for a 2D object (4 vertex)
	m_vertices =
	{
		Vertex(glm::vec2(-0.5f, -0.5f), glm::vec2(0,0)),
		Vertex(glm::vec2(-0.5f, 0.5f), glm::vec2(0,1)),
		Vertex(glm::vec2(0.5f, -0.5f), glm::vec2(1,0)),
		Vertex(glm::vec2(0.5f, 0.5f), glm::vec2(1,1))
	};

	//Default indices vector for a 2D object
	m_indices =
	{
		0,1,2,
		1,2,3
	};

	//Generate the neccesary buffers (VBO, EBO, VAO)
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	//Bind the VAO of the buffer
	glBindVertexArray(m_VAO);

	//Generate VBO and EBO and fill with the data
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

	//Link vertex position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_position));
	glEnableVertexAttribArray(0);

	//Link vertex texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_tex));
	glEnableVertexAttribArray(1);

	//Unbind VAO of the buffer
	glBindVertexArray(0);
}

//Draw the buffer data in OpenGL
void Buffer2D::Draw()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "OpenGL error after glUniformMatrix4fv: " << std::hex << err << std::endl;
	}
}

TextBuffer::TextBuffer()
{
	//Generate the neccesary buffers (VBO, EBO, VAO)
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
