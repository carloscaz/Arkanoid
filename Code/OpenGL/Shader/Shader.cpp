#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Shader::Shader(const char* _vertexFilename, const char* _fragmetFilename)
    :
    m_vertexShaderSource(_vertexFilename),
    m_fragmentShaderSource(_fragmetFilename)

{
    //Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    //Ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        //Open files
        vShaderFile.open(m_vertexShaderSource);
        fShaderFile.open(m_fragmentShaderSource);
        std::stringstream vShaderStream, fShaderStream;

        //Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        //Close file handlers
        vShaderFile.close();
        fShaderFile.close();

        //Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    m_vertexShaderSource = vertexCode.c_str();
    m_fragmentShaderSource = fragmentCode.c_str();

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    //Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);

    //Check for shader compile errors in vertex shader
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);

    //Check for shader compile errors in fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMEN::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Create Shader
    m_shaderID = glCreateProgram();
    glAttachShader(m_shaderID, vertexShader);
    glAttachShader(m_shaderID, fragmentShader);
    glLinkProgram(m_shaderID);
    //Check for linking errors
    glGetProgramiv(m_shaderID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

unsigned int Shader::GetShader()
{
    return m_shaderID;
}

void Shader::UseShader()
{
    glUseProgram(m_shaderID);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL error after glUseProgram: " << std::hex << err << std::endl;
    }
}

//Serach the matrix location in shader. If it exists, send the data to the shader
void Shader::SetMat4(const char* _location, const glm::mat4& _mat4)
{
    unsigned int loc = glGetUniformLocation(m_shaderID, _location);
    if (loc != -1)
    {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(_mat4));
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cerr << "OpenGL error after glUniformMatrix4fv: " << std::hex << err << std::endl;
        }
    }

    else
    {
        std::cout << "Matrix in location: " << _location << "not found" << std::endl;
    }
}
