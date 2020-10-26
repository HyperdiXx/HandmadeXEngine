#version 430 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec3 iTangent;
layout (location = 3) in vec3 iBitangent;
layout (location = 4) in vec2 iUV;

out VS_OUT {
    vec2 uv;
    vec3 normal;
    vec3 tangent;
    vec3 bitangent;
    vec3 world_pos;
    vec4 world_pos_light_space;
} vs_out;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 light_space_matrix;

void main()
{
    vs_out.uv = iUV;
    vs_out.normal = iNormal; 
    vs_out.tangent = iTangent;
    vs_out.bitangent = iBitangent;
    vs_out.world_pos = (model * vec4(iPos, 1.0)).xyz;
    vs_out.world_pos_light_space = light_space_matrix * vec4(vs_out.world_pos, 1.0);
    gl_Position = mvp * vec4(iPos, 1.0);
}