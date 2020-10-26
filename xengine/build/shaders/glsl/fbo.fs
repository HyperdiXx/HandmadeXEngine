#version 430 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D screenTexture;

void main()
{
    vec3 colorTex = texture(screenTexture, UV).rgb;
    float average = 0.2126 * colorTex.r + 0.7152 * colorTex.g + 0.0722 * colorTex.b;
    FragColor = vec4(average, average, average, 1.0);
} 