#shader vertex
#version 430 core
layout (location = 0) in vec3 aPos;

out vec3 UV;

uniform mat4 projection;
uniform mat4 view;

void main()
{
   UV = aPos;
   vec4 pos = projection * view * vec4(aPos, 1.0);
   gl_Position = pos.xyww; 
};

#shader pixel

#version 430 core
out vec4 frag_color;

in vec3 UV;
uniform samplerCube skybox;

void main()
{
   frag_color = texture(skybox, UV);
};