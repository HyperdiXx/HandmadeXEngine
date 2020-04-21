#version 330 core

out vec4 frag_color;

in vec3 world_pos;

uniform samplerCube env_map;

void main()
{		
    vec3 envColor = textureLod(env_map, world_pos, 0.0).rgb;
    
    // HDR tonemap and gamma correct
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2)); 
    
    frag_color = vec4(envColor, 1.0);
}