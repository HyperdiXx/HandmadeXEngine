#version 430 core
out vec4 frag_color;

in vec2 uv;

uniform sampler2D tex_diff;

void main()
{
    frag_color = texture(tex_diff, uv);
} 