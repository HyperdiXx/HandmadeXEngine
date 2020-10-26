#version 430 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 UV;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;


void main()
{
	gPosition = FragPos;
	gNormal = normalize(Normal);
	//GNormal = texture(texture_normal1, UV));
	//GNormal = normalize(GNormal * 2.0 - 1.0);
	gAlbedoSpec.rgb = texture(texture_diffuse1, UV).rgb;
	gAlbedoSpec.a = texture(texture_specular1, UV).r;
}