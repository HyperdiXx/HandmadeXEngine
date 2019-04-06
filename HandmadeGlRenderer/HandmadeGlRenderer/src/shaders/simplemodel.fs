#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

void main()
{    
    vec3 diftex = vec3(texture(texture_diffuse1, UV));
	vec3 normaltex = vec3(texture(texture_normal1, UV));
	vec3 spectex = vec3(texture(texture_specular1, UV));
	normaltex = normalize(normaltex * 2.0 - 1.0);
    FragColor = vec4(diftex + spectex + normaltex, 1.0);
}