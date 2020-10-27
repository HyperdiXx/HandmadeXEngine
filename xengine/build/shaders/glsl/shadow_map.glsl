#shader vertex
#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec2 UV;

out VS_OUT {
    vec3 world_pos;
    vec3 normal;
    vec2 uv;
    vec4 light_space_pos;
} vs_out;

uniform mat4 model;
uniform mat4 mvp;
uniform mat4 light_space_matrix;

void main()
{
    vs_out.world_pos = vec3(model * vec4(aPos, 1.0));
    vs_out.normal = transpose(inverse(mat3(model))) * aNormal;
    vs_out.uv = aUV;
    vs_out.light_space_pos = light_space_matrix * vec4(vs_out.world_pos, 1.0);
    gl_Position = mvp * vec4(aPos, 1.0);
}

#shader pixel

#version 430 core
out vec4 frag_color;

in VS_OUT {
    vec3 world_pos;
    vec3 normal;
    vec2 uv;
    vec4 light_space_pos;
} fs_in;

uniform sampler2D diff_tex;
uniform sampler2D shadow_map;

uniform vec3 light_pos;
uniform vec3 view_pos;

float calculate_shadows(vec4 light_space_pos)
{
    // Perspective divide
    vec3 projected_coord = light_space_pos.xyz / light_space_pos.w;
    
    // transform [-1, 1] to [0, 1] for depth
    projected_coord = projected_coord * 0.5 + 0.5;
 
    float sampled_depth = texture(shadow_map, projected_coord.xy).r; 
    
    float current_depth = projected_coord.z;
    
    vec3 normal = normalize(fs_in.normal);
    vec3 light_dir = normalize(light_pos - fs_in.world_pos);
    float bias = max(0.05 * (1.0 - dot(normal, light_dir)), 0.005);
    
    float shadow = 0.0;
    vec2 texel_size = 1.0 / textureSize(shadow_map, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcf = texture(shadow_map, projected_coord.xy + vec2(x, y) * texel_size).r; 
            shadow += current_depth - bias > pcf  ? 1.0 : 0.0;        
        }    
    }

    shadow /= 9.0;
    
    if(projected_coord.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{
   vec3 color = texture(diff_tex, fs_in.uv).rgb;
   vec3 normal = normalize(fs_in.normal);

   vec3 light_color = vec3(0.3);

   vec3 ambient = 0.3 * color;

   vec3 light_dir = normalize(light_pos - fs_in.world_pos);
   float diff = max(dot(light_dir, normal), 0.0);
   vec3 diffuse = diff * light_color;

   vec3 view_dir = normalize(view_pos - fs_in.world_pos);
   vec3 reflect_dir = reflect(-light_dir, normal);
   float spec = 0.0;
   vec3 halfway_dir = normalize(light_dir + view_dir);  
   spec = pow(max(dot(normal, halfway_dir), 0.0), 64.0);
   vec3 specular = spec * light_color;    

   float shadow = calculate_shadows(fs_in.light_space_pos);                      
   vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
   frag_color = vec4(lighting, 1.0);
};

