#shader vertex
#version 430 core
layout (location = 0) in vec3 aPos;

out vec3 world_pos;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    world_pos = aPos;  
    gl_Position =  projection * view * vec4(world_pos, 1.0);
}

#shader pixel
#version 430 core

out vec4 frag_color;

in vec3 world_pos;

uniform sampler2D equirectangular_map;

const vec2 invAtan = vec2(0.1591, 0.3183);

vec2 sample_spherical_map(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}

void main()
{		
    vec2 uv = sample_spherical_map(normalize(world_pos));
    vec3 color = texture(equirectangular_map, uv).rgb;
    
    frag_color = vec4(color, 1.0);
}