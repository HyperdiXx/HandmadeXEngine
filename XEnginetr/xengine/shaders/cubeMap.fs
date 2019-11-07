#version 330 core
out vec4 FragColor;

in vec3 UV;
uniform samplerCube skybox;

void main()
{
   vec3 colortest = vec3(1.0, 0.0, 0.0);
   FragColor = texture(skybox, UV);
   //FragColor = vec4(colortest, 1.0)
};