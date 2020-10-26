#version 430 core

layout (location = 0) in vec4  aPos;
layout (location = 1) in vec2  aUV;
layout (location = 2) in vec3  aNormal;
layout (location = 3) in uvec4 boneIds;
layout (location = 4) in vec4  boneWeights;

layout (std330) buffer bone_buffer
{
	mat4 bones[];
}

uniform mat4 mvp;

out vec2 uv;

void main()
{
	vec4 anim_vertex = vec4(0, 0, 0, 0);
	anim_vertex += bones[boneIds.w] * vec4(aPos, 1.0) * boneWeights.w;
	anim_vertex += bones[boneIds.x] * vec4(aPos, 1.0) * boneWeights.x;
	anim_vertex += bones[boneIds.y] * vec4(aPos, 1.0) * boneWeights.y;
	anim_vertex += bones[boneIds.z] * vec4(aPos, 1.0) * boneWeights.z;
	uv = aUV;
	gl_Position = mvp * vec4(anim_vertex.xyz, 1.0);
}