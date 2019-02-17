#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aUV;


out vec3 FragPos;
out vec3 Normal;
out vec3 UV;

uniform mat4 projection;
uniform mat4 view;


void main()
{
   FragPos = aPos;
   Normal = aNormal;
   UV = aUV;
   gl_Position = projection * view * vec4(aPos, 1.0);
};
