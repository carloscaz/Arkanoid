#pragma once
#include <glm/glm.hpp>

//Shader class to render objects in OpenGL
class Shader
{
private:
	const char* m_vertexShaderSource;
	const char* m_fragmentShaderSource;

	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;
	int retCode;
	char errorLog[1024];

	unsigned int m_shaderID;

public:
	Shader() {};
	Shader(const char* _vertexFilename, const char* _framentFilename);

	unsigned int GetShader();

	void UseShader();
	void SetVec3(const char* _location, const glm::vec2 _vec3);
	void SetMat4(const char* _location, const glm::mat4& _mat4);
};