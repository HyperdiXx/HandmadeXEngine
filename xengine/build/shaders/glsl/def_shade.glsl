#shader vertex
#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec3 frag_pos;
out vec2 uv;
out vec3 nnormal;

uniform mat4 mvp;

void main()
{
	uv = aUV;
	frag_pos = vec3(model * vec4(aPos, 1.0));
	mat3 normalMatrix = transpose(inverse(mat3(model)));
    	nnormal = normalMatrix * aNormal;
	gl_Position = mvp * vec4(aPos, 1.0);
}

#shader pixel
#version 430 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 uv;
in vec3 frag_pos
in vec3 nnormal;

uniform sampler2D texture_diff1;
uniform sampler2D texture_spec1;

void main()
{
	gPosition = frag_pos;
	gNormal = normalize(nnormal);
	//GNormal = texture(texture_normal1, UV));
	//GNormal = normalize(GNormal * 2.0 - 1.0);
	gAlbedoSpec.rgb = texture(texture_diffuse1, UV).rgb;
	gAlbedoSpec.a = texture(texture_specular1, UV).r;
}