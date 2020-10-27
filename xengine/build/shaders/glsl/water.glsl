#shader vertex
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec3 aBitangent;
layout (location = 4) in vec2 aUV;

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
//uniform mat4 light_space_matrix;

void main()
{
    vs_out.uv = aUV;
    vs_out.normal = aNormal; 
    vs_out.tangent = aTangent;
    vs_out.bitangent = aBitangent;
    vs_out.world_pos = (model * vec4(aPos, 1.0)).xyz;
    //vs_out.world_pos_light_space = light_space_matrix * vec4(vs_out.world_pos, 1.0);
    gl_Position = mvp * vec4(aPos, 1.0);
}

#shader pixel

#version 430 core
out vec4 frag_color;

in VS_OUT {
    vec2 uv;
    vec3 normal;
    vec3 tangent;
    vec3 bitangent;
    vec3 world_pos;
    vec4 world_pos_light_space;
} fs_in;

uniform sampler2D tex_diff;

void main()
{
    frag_color = texture(tex_diff, fs_in.uv);
}