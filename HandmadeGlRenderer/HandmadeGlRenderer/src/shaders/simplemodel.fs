#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

void main()
{    
    vec4 diftex = texture(texture_diffuse1, UV);
	vec4 normaltex = texture(texture_normal1, UV);
	normaltex = normalize(normaltex * 2.0 - 1.0);
    FragColor = diftex;
}