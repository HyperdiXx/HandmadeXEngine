#version 330 core

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