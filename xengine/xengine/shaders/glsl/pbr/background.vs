#version 330 core
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