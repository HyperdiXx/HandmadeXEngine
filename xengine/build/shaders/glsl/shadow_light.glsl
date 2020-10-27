#shader vertex
#version 430 core
layout (location = 0) in vec3 aPos;

uniform mat4 lightmatrix;
uniform mat4 model;

void main()
{
    gl_Position = lightmatrix * model * vec4(aPos, 1.0);
}

#shader pixel
#version 430 core

void main()
{
   //gl_FragDepth = gl_FragCoord.z;
};