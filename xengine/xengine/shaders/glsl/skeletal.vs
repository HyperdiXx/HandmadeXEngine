#version 330 core

layout (location = 0) in vec4  aPos;
layout (location = 1) in vec2  aUV;
layout (location = 2) in vec3  aNormal;
layout (location = 3) in uvec4 bone_ids;
layout (location = 4) in vec4  bone_weights;

layout (std330) buffer bone_buffer
{
	mat4 bones[];
}

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 uv;

void main()
{
	vec4 anim_vertex = vec4(0, 0, 0, 0);
	anim_vertex += bones[bone_ids.w] * vec4(aPos, 1.0) * bone_weights.w;
	anim_vertex += bones[bone_ids.x] * vec4(aPos, 1.0) * bone_weights.x;
	anim_vertex += bones[bone_ids.y] * vec4(aPos, 1.0) * bone_weights.y;
	anim_vertex += bones[bone_ids.z] * vec4(aPos, 1.0) * bone_weights.z;
	uv = aUV;
	gl_Position = projection * view * model * vec4(anim_vertex.xyz, 1.0);
}