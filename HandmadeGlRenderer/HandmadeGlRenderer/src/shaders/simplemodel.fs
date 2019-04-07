#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 UV;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{    
	vec3 diffusecolor = vec3(0.8, 0.8, 0.8);
	vec3 speccolor = vec3(1.0, 1.0, 1.0);

    vec3 diftex = vec3(texture(texture_diffuse1, UV));
	vec3 normaltex = vec3(texture(texture_normal1, UV));
	vec3 spectex = vec3(texture(texture_specular1, UV));
	normaltex = normalize(normaltex * 2.0 - 1.0);
	
	vec3 ambient = 0.1 * diftex;

    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    float diff = max(dot(normaltex, lightDir), 0.0);
    vec3 diffuse = diff * diftex;  
    
    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normaltex);
    vec3 halfwayDir = normalize(lightDir + viewDir);    
    float spec = pow(max(dot(normaltex, halfwayDir), 0.0), 32.0);
    vec3 specular = speccolor * spec * spectex;  
 

	vec3 res = ambient + diffuse;
	
    FragColor = vec4(res, 1.0);
}