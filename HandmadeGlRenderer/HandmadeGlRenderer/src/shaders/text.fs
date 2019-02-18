#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D texture;
uniform vec3 color;

void main()
{
   color = vec3(1.0, 0.0, 0.0);
   FragColor = texture(uv, UV).r * color;
};