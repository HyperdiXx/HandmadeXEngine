#version 330 core

out vec4 ResColor;

in vec2 UV;
in vec3 VertexPos;
in vec3 Normal;

const float PI = 3.14159265359;

uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

uniform vec3 camPos;
uniform vec3 lightPos[4]; 
uniform vec3 lightColor[4]; 


float NDF(vec3 n, vec3 h, float rough)
{
	float a = rough * rough;
	float a2 = a * a;
	float nDot = max(dot(n, h), 0.0);
	float n2Dot = nDot * nDot;
	
	
	float res = (n2Dot * (a2 - 1.0) + 1.0);

	res = PI * res * res;

	return a2 / max(res, 0.001);
}

float SchlickHelper(float ndotV, float rough)
{
	float r = rough + 1.0;
	float k = (r * r) / 8.0;
	float nom = ndotV;
	float res = ndotV * (1.0 - k) + k;

	return nom / res;
}


float GF(vec3 n, vec3 v, vec3 l, float rough)
{
	float ndotview = max(dot(n, v), 0.0);
	float nodtlight = max(dot(n, l), 0.0);

	float g1 = SchlickHelper(ndotview, rough);
	float g2 = SchlickHelper(nodtlight, rough);

	return g1 * g2;
}

float FF(float c, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(1.0 - c, 5.0);
}


void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewdir = normalize(camPos - VertexPos);

	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);

	vec3 Lo = vec3(0.0);

	for(int i = 0; i < 4; ++i)
	{
		vec3 lightdir = (lightPos[i] - VertexPos);
		vec3 halfway = (lightdir + viewdir);
		float distance = length(lightPos[i] - VertexPos);
		float atten = 1.0 / (distance * distance);
		vec3 rad = lightColor[i] * atten;

		float NDFuncvar = NDF(norm, halfway, roughness);
		float Gfuncvar = GF(norm, viewdir, lightdir, roughness);
		vec3 fresnelvar = FF(clamp(dot(halfway, viewdir), 0.0, 1.0), F0);

		vec3 nominator = NDFuncvar * Gfuncvar * fresnelvar;
		float denominator = 4 * max(dot(norm, viewdir), 0.0) * max(dot(norm, lightdir), 0.0);
		vec3 specular = nominator / max(denominator, 0.001);


		vec3 kS = fresnelvar;
		vec3 kD = vec3(1.0) - kS;
		kD *= 1.0 - metallic;
		float NdotL = max(dot(norm, lightdir), 0.0);        

        Lo += (kD * albedo / PI + specular) * rad * NdotL;

	}


	vec3 ambient = vec3(0.03) * albedo * ao;
	vec3 color = ambient + Lo;

	color = color / (color + vec3(1.0));

	color = pow(color, vec3(1.0 / 2.2));

	ResColor = vec4(color, 1.0);
}



