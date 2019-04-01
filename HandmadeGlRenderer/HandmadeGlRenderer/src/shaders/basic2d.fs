#version 330 core

layout (location = 0) out vec4 FragColor;

in d
{
	vec4 pos;
	vec4 color;
} fs_in;


void main()
{
	FragColor = fs_in.color;
}