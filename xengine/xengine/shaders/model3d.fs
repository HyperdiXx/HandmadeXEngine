#version 330 core
out vec4 frag_color;

in vec2 uv;

uniform sampler2D tex_diff1;
uniform sampler2D tex_norm1;
uniform sampler2D tex_spec1;

void main()
{
    frag_color = texture(tex_diff1, uv);
    //frag_color = vec4(1.0, 0.0, 0.0, 1.0);
}