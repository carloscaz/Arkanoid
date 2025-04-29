#pragma once
#include "../Component.h"
#include "../OpenGL/Buffer/Buffer.h"
#include "../OpenGL/Shader/Shader.h"
#include "../OpenGL/Texture/Texture.h"

//Component to render elements in the screen with OpenGL
class RenderComponent : public Component
{
private:
	Buffer2D m_buffer;
	Shader m_shader;
	Texture m_texture;
public:
	RenderComponent() {};
	RenderComponent(const Shader& m_shader, const Texture& _texture);

	Buffer2D& GetBuffer();
	Shader& GetShader();
	Texture& GetTexture();
};