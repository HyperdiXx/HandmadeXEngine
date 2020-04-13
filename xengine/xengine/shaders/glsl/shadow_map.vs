#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec2 UV;

out VS_OUT {
    vec3 world_pos;
    vec3 normal;
    vec2 uv;
    vec4 light_space_pos;
} vs_out;

uniform mat4 model;
uniform mat4 mvp;
uniform mat4 light_space_matrix;

void main()
{
    vs_out.world_pos = vec3(model * vec4(aPos, 1.0));
    vs_out.normal = transpose(inverse(mat3(model))) * aNormal;
    vs_out.uv = aUV;
    vs_out.light_space_pos = light_space_matrix * vec4(vs_out.world_pos, 1.0);
    gl_Position = mvp * vec4(aPos, 1.0);
}