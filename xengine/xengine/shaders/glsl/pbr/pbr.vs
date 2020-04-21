#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec2 uv;
out vec3 world_pos;
out vec3 normal;

uniform mat4 model;
uniform mat4 mvp;

void main()
{
    uv = aUV;
    world_pos = vec3(model * vec4(aPos, 1.0));
    normal = mat3(model) * aNormal;
    gl_Position = mvp * vec4(aPos, 1.0);
}