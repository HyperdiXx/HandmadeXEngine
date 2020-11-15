#shader vertex
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
//layout (location = 2) in vec3 aTangent;
//layout (location = 3) in vec3 aBitangent;
layout (location = 3) in vec2 aUV;

out vec3 frag_posWS;
out mat3 tbn;
out vec2 uv;
out vec3 normalout;

uniform mat4 vp;
uniform mat4 model;

void main()
{
	uv = aUV;
	frag_posWS = (model * vec4(aPos, 1.0)).xyz;

	mat3 normalMatrix = transpose(inverse(mat3(model)));
    
	//vec3 T = normalize(normalMatrix * aTangent);
	//vec3 B = normalize(normalMatrix * aBitangent);
	vec3 N = normalize(normalMatrix * aNormal);

	//tbn = mat3(T, B, N);
	normalout = N;

	gl_Position = vp * model * vec4(aPos, 1.0);
}

#shader pixel
#version 430 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 uv;
in vec3 frag_posWS;
in vec3 normalout;
in mat3 tbn;

uniform sampler2D tex_diff;
uniform sampler2D tex_norm;
uniform sampler2D tex_spec;

void main()
{	
	gPosition = frag_posWS;

	//vec3 normal = texture(tex_norm, uv).rgb; 
	//normal = normal * 2.0 - 1.0;
	gNormal = normalize(normalout);
	
	gAlbedoSpec.rgb = texture(tex_diff, uv).rgb;
	gAlbedoSpec.a = texture(tex_spec, uv).r;
}