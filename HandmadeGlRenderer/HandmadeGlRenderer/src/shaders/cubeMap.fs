#version 330 core
out vec4 FragColor;

in vec3 texCoords;
uniform samplerCube cubemap;

void main()
{
   vec3 colortest = vec3(1.0, 0.0, 0.0);
   FragColor = texture(cubemap, texCoords);
};