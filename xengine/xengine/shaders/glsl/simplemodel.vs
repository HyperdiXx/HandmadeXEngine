#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;  

out vec3 FragPos;
out vec2 UV;
out vec3 Normal;

uniform mat4 model;
uniform mat4 viewproj;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
    UV = aUV;
    //mat3 normalMatrix = transpose(inverse(mat3(model)));

	//Normal = normalMatrix * aNormal;
    gl_Position = viewproj * model * vec4(aPos, 1.0);
}