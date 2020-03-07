#version 330 core
out vec4 frag_color;

in vec2 uv;
in vec3 normal;
in vec3 frag_pos;

uniform sampler2D tex_diff1;
uniform sampler2D tex_norm1;
uniform sampler2D tex_spec1;
uniform float intensity;

uniform vec3 dir_light_color;
uniform vec3 light_pos;
uniform vec3 cam_pos;

vec3 gamma_correction(vec3 color) 
{
    return pow(color, vec3(0.4545));
}

void main()
{
    vec3 diffuse = gamma_correction(texture(tex_diff1, uv).rgb);
     
    vec3 normalt = vec3(texture(tex_norm1, uv).rgb);
    normalt = normalize(normalt * 2.0 - 1.0);
    
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff_coef = max(dot(normalt, light_dir), 0.0);

    diffuse = dir_light_color * intensity * diff_coef * diffuse;

	vec3 res = diffuse;

    frag_color = vec4(res, 1.0);  
}