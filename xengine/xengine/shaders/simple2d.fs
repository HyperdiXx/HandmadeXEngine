#version 330 core
out vec4 frag_color;

in vec2 uv;
uniform sampler2D textureColor;

void main()
{
    frag_color = texture(textureColor, uv);
	//frag_color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
} 