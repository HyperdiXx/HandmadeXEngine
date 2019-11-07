#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 HDRColor;

in VS_OUT
{
	vec3 FragPos;
	vec3 Normal;
	vec2 UV;
} fs_in;

struct Lighting
{
	vec3 Color;
	vec3 Pos;
};


uniform vec3 viewPos;
uniform sampler2D diffuseMap;
uniform Lighting light;


void main()
{
	vec3 textcolor = texture(diffuseMap, fs_in.UV).rgb;
	vec3 normal = normalize(fs_in.Normal);

	float ambient = 0.1;

	vec3 ambientColor = ambient * textcolor;

	vec3 lightColor = vec3(0.0);
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);

	for(int i = 0; i < 4; ++i)
	{
		vec3 lightDir = normalize(light.Pos[i] - fs_in.FragPos);
		float diff = max(dot(lightDir, normal), 0.0);
		vec3 res = light.Color[i] * diff * textcolor;

		float distance = length(fs_in.FragPos - light[i].Pos);
        res *= 1.0 / (distance * distance);
        lightColor += res;

	}
	vec3 result = ambientColor + lightColor;

	float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));

    if(brightness > 1.0)
        HDRColor = vec4(result, 1.0);
    else
        HDRColor = vec4(0.0, 0.0, 0.0, 1.0);
    FragColor = vec4(result, 1.0);

}

