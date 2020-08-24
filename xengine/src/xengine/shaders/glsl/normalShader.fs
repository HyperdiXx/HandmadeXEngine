#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 UV;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform vec3 lightPos;
uniform vec3 viewPos;


uniform sampler2D diffuseMap;
uniform sampler2D normalMap;



void main()
{
	vec3 textureColor = texture(diffuseMap, UV).rgb;
	vec3 normal = texture(normalMap, UV).rgb;

	normal = normalize(normal * 2.0 - 1.0);

	float ambient = 0.1;
	float shiness = 64.0;

	vec3 ambientColor = ambient * textureColor;

	vec3 lightDirectionForDiffuse = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	float diff = max(dot(lightDirectionForDiffuse, normal), 0.0);
	vec3 diffuseColor = diff * textureColor;

	vec3 viewDirForSpecular = normalize(fs_in.TangentViewPos - fs_in,TangentFragPos);
	vec3 reflecttVec = reflect(-lightDirectionForDiffuse, normal);
	vec3 halfwayVec = normalize(lightDirectionForDiffuse + viewDirForSpecular);

	float spec = pow(max(dot(normal, halfwayVec), 0.0), shiness);

	vec3 specularColor = vec3(0.2) * spec;

	FragColor = vec4(ambientColor + diffuseColor + specularColor, 1.0);
}