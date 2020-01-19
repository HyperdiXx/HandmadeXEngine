#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iUV;

out vec2 uv;

uniform mat4 model;
uniform mat4 viewproj;

void main()
{
    uv = iUV;
    gl_Position = viewproj * model * vec4(iPos, 1.0);
}