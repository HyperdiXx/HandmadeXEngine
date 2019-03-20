#version 330 core
layout (location = 0) out vec3 GPos;
layout (location = 1) out vec3 GNormal;
layout (location = 2) out vec4 GSpeccolor;


in vec3 FragPos;
in vec2 UV;
in vec3 Normal;


uniform sampler2D tex1;
uniform sampler2D tex2;


void main()
{
	GPos = FragPos;
	GNormal = normalize(Normal);
	GSpeccolor.rgb = texture(tex1, UV).rgb;
	GSpeccolor.a = texture(tex2, UV).r;
}