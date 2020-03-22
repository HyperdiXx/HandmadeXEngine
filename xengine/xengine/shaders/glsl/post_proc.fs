#version 330 core
out vec4 frag_color;

in vec2 out_uv;

uniform sampler2D tex_diff; 

const float offset = 1.0 / 300.0;

vec3 gamma_correction(vec3 input)
{
	return pow(input, vec3(0.4545));
}

void main()
{	
	float kernel[9] = float[]
	(		
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

	float kernel_blur[9] = float[]
	(
		1.0 / 16, 2.0 / 16, 1.0 / 16,
    	2.0 / 16, 4.0 / 16, 2.0 / 16,
    	1.0 / 16, 2.0 / 16, 1.0 / 16  
	);
	
	vec2 offsets[9] = vec2[]
	(
		vec2(-offset,  offset), 
		vec2( 0.0,    offset), 
		vec2( offset,  offset), 
		vec2(-offset,  0.0),   
		vec2( 0.0,    0.0),   
		vec2( offset,  0.0),   
		vec2(-offset, -offset), 
		vec2( 0.0,   -offset), 
		vec2( offset, -offset)      
	);

	vec3 kernel_color = vec3(0.0);
	vec3 sampled[9];
	for(int i = 0; i < 9; i++)
	{
		 sampled[i] = vec3(texture(tex_diff, out_uv.st + offsets[i]));
		 kernel_color += sampled[i] * kernel_blur[i];
	}

	vec3 gamma_corrected_color = gamma_correction(kernel_color);

	frag_color = vec4(gamma_corrected_color, 1.0);
}