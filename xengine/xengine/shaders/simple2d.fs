#version 330 core
out vec4 frag_color;

in vec2 uv;

uniform sampler2D texture_diff;

void main()
{
    frag_color = texture(texture_diff, uv);
    //frag_color = vec4(1.0, 0.0, 0.0, 1.0);
} 