#shader vertex
#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec2 uv;

uniform mat4 model;
uniform mat4 mvp;

void main()
{
    uv = aUV;    
    gl_Position = mvp * vec4(aPos, 1.0);
}

#shader pixel
#version 430 core
out vec4 frag_color;

in vec2 UV;

uniform vec3 color;
uniform bool shadows_enabled;
uniform vec3 cam_pos;
uniform vec3 light_pos;

void main()
{    
    frag_color = vec4(1.0, 0.0, 0.0, 1.0);
}  