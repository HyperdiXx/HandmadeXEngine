#version 430 core
out vec4 frag_color;

in vec2 out_uv;

uniform sampler2D tex_diff; 

vec3 gamma_correction(vec3 input)
{
	return pow(input, vec3(0.4545));
}

void main()
{
	frag_color =  vec4(gamma_correction(texture(tex_diff, out_uv).rgb), 1.0);
}