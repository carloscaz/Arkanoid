#pragma once

//Texture to render sprites in OpenGL
class Texture
{
private:
	unsigned int m_tex;
	int m_height, m_width;

public:
	Texture() {};
	Texture(const char* _filename);

	void BindTexture();

	int GetHeight();
	int GetWidth();
};