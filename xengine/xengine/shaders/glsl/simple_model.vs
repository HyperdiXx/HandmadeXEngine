#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

out vec2 uv;

uniform mat4 model;
uniform mat4 mvp;

void main()
{
    uv = aUV;    
    gl_Position = mvp * vec4(aPos, 1.0);
}