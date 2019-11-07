#version 330 core
layout (location = 0) out vec4 FragColor;

in vec2 UV;

uniform sampler2D diffuseTexture;
uniform bool hor;
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);


void main()
{
	vec2 singletexel = 1.0 / textureSize(diffuseTexture, 0);
	vec3 res = texture(diffuseTexture, UV);.rgb * weight[0];
	if(hor)
	{
		for(int i = 1; i < 5; ++i)
		{
			res += texture(diffuseTexture, UV + vec2(singletexel.x * i, 0.0)).rgb * weight[i];
			res += texture(diffuseTexture, UV - vec2(singletexel.x * i, 0.0)).rgb * weight[i];
		}
	}
	else
	{
		for(int i = 1; i < 5; ++i)
		{
			res += texture(diffuseTexture, UV + vec2(0.0, singletexel.y * i)).rgb * weight[i];
			res += texture(diffuseTexture, UV - vec2(0.0, singletexel.y * i)).rgb * weight[i];
		}
	}
}