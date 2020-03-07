#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iUV;

out vec2 uv;

uniform mat4 mvp;
uniform mat4 model;

void main()
{
    uv = iUV;
    vec3 world_pos = (model * vec4(iPos, 1.0)).xyz;
    gl_Position = mvp * vec4(iPos, 1.0);
}