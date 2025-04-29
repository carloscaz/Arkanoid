#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTex;

//MVP matrix
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

out vec2 fTex;

void main()
{
    gl_Position = Proj * View * Model * vec4(vPos, 1.0);
    fTex = vTex;

}
