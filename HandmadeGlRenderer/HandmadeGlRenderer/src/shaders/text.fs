#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D textureUV;
uniform vec3 color;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(textureUV, UV).r);
    FragColor = vec4(color, 1.0) * sampled;
}  