#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 modelInvTransp;
uniform vec4 clipPlane;

out vec4 vertexPos;
out vec3 Normal;

void main() 
{
   mat4 MVP = projection * view * model;
   gl_Position = MVP * vec4(aPos, 1.0);
   vertexPos = model * vec4(aPos, 1.0);
   Normal = normalize(modelInvTransp * aNormal);
   gl_ClipDistance[0] = dot(vertexPos, clipPlane);
}
