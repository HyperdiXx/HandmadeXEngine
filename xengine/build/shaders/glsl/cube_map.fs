#version 430 core
out vec4 frag_color;

in vec3 UV;
uniform samplerCube skybox;

void main()
{
   frag_color = texture(skybox, UV);
};