#version 330 core
out vec4 frag_color;

in vec3 world_pos;

uniform samplerCube environment_map;

const float PI = 3.14159265359;

void main()
{		
    vec3 N = normalize(world_pos);

    vec3 irradiance = vec3(0.0);   
    
    vec3 up    = vec3(0.0, 1.0, 0.0);
    vec3 right = cross(up, N);
    up         = cross(N, right);
       
    float sample_delta = 0.025;
    float nr_samples = 0.0f;
    for(float phi = 0.0; phi < 2.0 * PI; phi += sample_delta)
    {
        for(float theta = 0.0; theta < 0.5 * PI; theta += sample_delta)
        {
            // spherical to cartesian (in tangent space)
            vec3 tangent = vec3(sin(theta) * cos(phi),  sin(theta) * sin(phi), cos(theta));
            
            // tangent space to world
            vec3 sampled_vec = tangent.x * right + tangent.y * up + tangent.z * N; 

            irradiance += texture(environment_map, sampled_vec).rgb * cos(theta) * sin(theta);
            nr_samples++;
        }
    }

    irradiance = PI * irradiance * (1.0 / float(nr_samples));
    
    frag_color = vec4(irradiance, 1.0);
}