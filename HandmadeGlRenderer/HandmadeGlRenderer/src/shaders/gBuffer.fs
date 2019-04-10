#version 330 core
layout (location = 0) out vec3 GPos;
layout (location = 1) out vec3 GNormal;
layout (location = 2) out vec4 GColor;


in vec3 FragPos;
in vec2 UV;
in vec3 Normal;

uniform sampler2D tex1_dif;
uniform sampler2D tex2_normal;
uniform sampler2D tex3_spec;


void main()
{
	GPos = FragPos;
	GNormal = normalize(Normal);
	//GNormal = texture(tex2_normal, UV));
	//GNormal = normalize(GNormal * 2.0 - 1.0);
	GColor.rgb = texture(tex1_dif, UV).rgb;
	GColor.a = texture(tex3_spec, UV).r;
}