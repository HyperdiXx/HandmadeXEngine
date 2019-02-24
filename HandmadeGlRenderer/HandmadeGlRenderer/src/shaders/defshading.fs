#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D GPos;
uniform sampler2D GNormal;
uniform sampler2D GSpeccolor;

struct Light {
    vec3 pos;
    vec3 color;
    
    float linear;
    float quadratic;
};
const int NR_LIGHTS = 32;
uniform Light lights[NR_LIGHTS];
uniform vec3 viewPos;

void main()
{             
    vec3 FragPos = texture(GPos, UV).rgb;
    vec3 Normal = texture(GNormal, UV).rgb;
    vec3 diffuseRes = texture(GSpeccolor, UV).rgb;
    float specularRes = texture(GSpeccolor, UV).a;
    
	flota ambient = 0.1;

    vec3 lighting  = diffuseRes * ambient; 
    vec3 viewDir  = normalize(viewPos - FragPos);
    for(int i = 0; i < NR_LIGHTS; ++i)
    {

        vec3 lightDir = normalize(lights[i].pos - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * diffuseRes * lights[i].color;

        vec3 halfwayDir = normalize(lightDir + viewDir);  
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
        vec3 specular = lights[i].color * spec * specularRes;
        // attenuation
        float distance = length(lights[i].pos - FragPos);
        float attenuation = 1.0 / (1.0 + lights[i].linear * distance + lights[i].quadratic * distance * distance);
        diffuse *= attenuation;
        specular *= attenuation;
        lighting += diffuse + specular;        
    }
    FragColor = vec4(lighting, 1.0);
}