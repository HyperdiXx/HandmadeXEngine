#shader vertex
#version 430 core
layout (location = 0) in vec3 aPos;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0);
}

#shader pixel
#version 430 core
out vec4 frag_color;

uniform vec4 u_color;

void main()
{
    frag_color = u_color;
} 