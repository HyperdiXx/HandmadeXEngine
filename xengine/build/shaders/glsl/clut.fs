#shader vertex
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

#shader pixel
#version 430 core

out vec4 frag_color;

in vec2 UV;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec2 pos = gl_TexCoord[0].xy;
    vec4 color = texture(texture1, pos);
    vec2 index = vec2(color.r + paletteIndex, 0);
    vec4 indexedColor = texture2D(colorTable, index);
    frag_color = indexedColor;      
}


