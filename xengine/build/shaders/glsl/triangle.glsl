#shader vertex
#version 430 core

layout (location = 0) in vec3 aPos;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
};

#shader pixel
#version 430 core

out vec4 frag_color;

void main()
{
   frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
};