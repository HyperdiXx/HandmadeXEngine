#shader vertex
#version 430 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 light_space_matrix;

void main()
{
    gl_Position = light_space_matrix * model * vec4(aPos, 1.0);
}

#shader pixel

#version 430 core

void main()
{
   
};
