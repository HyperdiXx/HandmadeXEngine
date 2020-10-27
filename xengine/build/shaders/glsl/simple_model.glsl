#shader vertex
#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec2 uv;

uniform mat4 model;
uniform mat4 mvp;

void main()
{
    uv = aUV;    
    gl_Position = mvp * vec4(aPos, 1.0);
}

#shader pixel
#version 430 core
out vec4 frag_color;

in vec2 uv;

uniform sampler2D tex_diff;

void main()
{
    frag_color = texture(tex_diff, uv);
} 