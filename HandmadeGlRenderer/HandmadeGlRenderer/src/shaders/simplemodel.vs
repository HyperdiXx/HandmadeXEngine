#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;  


out vec3 FragPos;
out vec2 UV;
out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

uniform mat4 model;
uniform mat4 viewproj;

uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
    UV = aUV;
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    TangentLightPos = TBN * lightPos;
    TangentViewPos  = TBN * camPos;
    TangentFragPos  = TBN * FragPos;

    gl_Position = viewproj * model* vec4(aPos, 1.0);
}