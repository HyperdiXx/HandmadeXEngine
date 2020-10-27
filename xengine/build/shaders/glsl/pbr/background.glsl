#shader vertex
#version 430 core
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;

out vec3 world_pos;

void main()
{
    world_pos = aPos;
	
	mat4 rotat_v = mat4(mat3(view));
	vec4 clip_pos = projection * rotat_v * vec4(world_pos, 1.0);

	// store depth as 1.0 
	gl_Position = clip_pos.xyww;
}

#shader pixel
#version 430 core

out vec4 frag_color;

in vec3 world_pos;

uniform samplerCube env_map;

void main()
{		
    vec3 env_vector = normalize(world_pos);	
    vec3 envColor = textureLod(env_map, env_vector, 0.0).rgb;
    
    // HDR tonemap and gamma correct
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(0.4545)); 
    
    frag_color = vec4(envColor, 1.0);
}