#version 330 core
out vec4 frag_color;

in vec2 uv;

uniform sampler2D tex_diff1;
uniform sampler2D tex_norm1;
uniform sampler2D tex_spec1;

vec3 gamma_correction(vec3 color) 
{
    return pow(color, vec3(0.4545));
}

void main()
{
    vec3 diffuse = gamma_correction(texture(tex_diff1, uv).rgb);
	
    frag_color = vec4(diffuse, 1.0);
    //frag_color = texture(tex_diff1, uv);    
}