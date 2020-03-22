#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 projection;
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

out d
{
	vec4 pos;
	vec4 color;

} vs_out;


void main()
{
	gl_Position = projection * view * model * aPos;
	vs_out.pos = model * aPos;
	vs_out.color = aColor;
}