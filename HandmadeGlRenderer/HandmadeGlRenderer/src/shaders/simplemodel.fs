#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 UV;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

void main()
{    
    vec3 diftex = vec3(texture(texture_diffuse1, UV));
	vec3 normaltex = vec3(texture(texture_normal1, UV));
	vec3 spectex = vec3(texture(texture_specular1, UV));
	normaltex = normaltex * 2.0 - 1.0;

    //vec3 resnormal = Normal + normaltex.x * input.tangent + bumpMap.y * input.binormal;
	
    //resnormal = normalize(resnormal);


    FragColor = vec4(diftex, 1.0);
}