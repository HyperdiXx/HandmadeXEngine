#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D screenTexture;

void main()
{
	//FragColor = texture(screenTexture, UV);
    float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    //FragColor = vec4(average, average, average, 1.0);
	FragColor = vec4(0.0, 1.0, 0.0, 1.0);
} 