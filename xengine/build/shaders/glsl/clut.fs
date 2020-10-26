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


