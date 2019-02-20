#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 UV;
} fs_in;

uniform sampler2D floorTexture;
uniform vec3 lightPos;
uniform vec3 viewPos;

//blinnphonglighting
void main()
{   
    vec3 colorTexture = texture(floorTexture, fs_in.UV).rgb;

    vec3 ambient = 0.05 * colorTexture;

    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    vec3 normal = normalize(fs_in.Normal);

    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * colorTexture;

    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;

    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.3) * spec; 
	
	float distance = length(lightPos - fs_in.FragPos);
	float atten = 1.0 / distance;

	ambient *= atten;
	diffuse *= atten;
	specular *= atten;
	
    FragColor = vec4(ambient + diffuse + specular, 1.0);
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);

	FragColor.rgb = pow(FragColor.rgb, vec3(1 / 2.2));
}