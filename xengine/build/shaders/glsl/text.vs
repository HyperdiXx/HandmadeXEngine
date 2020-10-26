#version 430 core
layout (location = 0) in vec4 aPos;

out vec2 UV;

uniform mat4 projection;

void main()
{
   UV = aPos.zw;
   gl_Position = projection * vec4(aPos.xy, 0.0, 1.0);
};
