#version 430 core

layout (location = 0) out vec4 GLColor;

uniform vec3 lightColor;

void main()
{
	GLColor = vec4(lightColor, 1.0);
}

