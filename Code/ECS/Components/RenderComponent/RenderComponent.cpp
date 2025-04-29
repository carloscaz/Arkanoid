#include "RenderComponent.h"

RenderComponent::RenderComponent(const Shader& _shader, const Texture& _texture) :
	m_buffer(),
	m_shader(_shader),
	m_texture(_texture)
{}

Buffer2D& RenderComponent::GetBuffer()
{
	return m_buffer;
}

Shader& RenderComponent::GetShader()
{
	return m_shader;
}

Texture& RenderComponent::GetTexture()
{
	return m_texture;
}