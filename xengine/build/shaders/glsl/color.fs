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