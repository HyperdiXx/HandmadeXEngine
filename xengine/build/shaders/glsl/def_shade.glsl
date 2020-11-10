#shader vertex
#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec4 frag_pos;
out vec2 uv;
out vec3 normalout;

uniform mat4 vp;
uniform mat4 model;

void main()
{
	uv = aUV;
	frag_pos = model * vec4(aPos, 1.0);
	mat3 normalMatrix = transpose(inverse(mat3(model)));
    normalout = normalMatrix * aNormal;
	
	gl_Position = vp * frag_pos;
}

#shader pixel
#version 430 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 uv;
in vec3 frag_pos
in vec3 normalout;

uniform sampler2D tex_diff1;
uniform sampler2D tex_spec1;

void main()
{	
	gPosition = frag_pos;
	gNormal = normalize(normalout);
	//GNormal = texture(texture_normal1, uv));
	//GNormal = normalize(GNormal * 2.0 - 1.0);
	gAlbedoSpec.rgb = texture(tex_diff1, uv).rgb;
	gAlbedoSpec.a = texture(tex_spec1, uv).r;
}