#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <iostream>

//Texture to render sprites in OpenGL
Texture::Texture(const char* _filename)
{
    //Bind texture data in OpenGL
    glGenTextures(1, &m_tex);
    glBindTexture(GL_TEXTURE_2D, m_tex);

    //Configure Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    int nrChannels;

    //Load the image
    unsigned char* data = stbi_load(_filename, &m_width, &m_height, &nrChannels, 0);
    if (data)
    {
        if (nrChannels == 4) //If 4 channels, image with RGBA
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 3) //If 3 channels, image with RGB
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB,
                GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 2) //If 2 channels, image with RG
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, m_width, m_height, 0, GL_RG,
                GL_UNSIGNED_BYTE, data);
        }
        else //Image with R
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED,
                GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    else
    {
        std::cout << "Texture not found\n";
    }

    stbi_image_free(data);

}

void Texture::BindTexture()
{
    glBindTexture(GL_TEXTURE_2D, m_tex);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL error after glBindTexture: " << std::hex << err << std::endl;
    }
}

int Texture::GetHeight()
{
    return m_height;
}

int Texture::GetWidth()
{
    return m_width;
}
