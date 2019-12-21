#version 330 core
out vec4 frag_color;

in vec3 color;
in vec2 uv;
uniform sampler2D textureDiffuse;

void main()
{
    frag_color = texture(textureDiffuse, uv);
	//frag_color = vec4(color, 1.0f);
} 