#shader vertex
#version 430 core
layout (location = 0) in vec4 aPos;

out vec2 UV;

uniform mat4 projection;

void main()
{
   UV = aPos.zw;
   gl_Position = projection * vec4(aPos.xy, 0.0, 1.0);
};

#shader pixel
#version 430 core

out vec4 frag_color;

in vec2 UV;

uniform sampler2D textureUV;
uniform vec3 color;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(textureUV, UV).r);
    frag_color = vec4(color, 1.0) * sampled;
}  