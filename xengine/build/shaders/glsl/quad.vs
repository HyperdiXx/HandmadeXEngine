#version 430 core

int indices[6] = int[](0, 1, 2, 2, 1, 3);

vec3 vertices[4] = vec3[]
(
    vec3(-1, -1, 0),
    vec3(1, -1, 0),
    vec3(-1, 1, 0),
    vec3(1, 1, 0)
);

vec2 uv[4] = vec2[]
(
    vec2(0, 0),
    vec2(1, 0),
    vec2(0, 1),
    vec2(1, 1)
);

out vec3 out_pos;
out vec2 out_uv;

void main() 
{
    int index = indices[gl_VertexID];
    
    out_pos = vertices[index];
    out_uv = uv[index];
    
    gl_Position = vec4(vertices[index], 1.0);
}