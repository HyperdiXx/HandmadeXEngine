#version 430 core
out vec4 frag_color;

struct material 
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct direction_light
{
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct point_light 
{    
	vec3 position;
  
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct spot_light 
{
    vec3 position;
    vec3 direction;
    float cut_off;
    float outer_cut_off;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

in VS_OUT {
    vec2 uv;
    vec3 normal;
    vec3 tangent;
    vec3 bitangent;
    vec3 world_pos;
    vec4 world_pos_light_space;
} fs_in;

uniform sampler2D tex_diff1;
uniform sampler2D tex_norm1;
uniform sampler2D tex_spec1;

uniform sampler2D shadow_map;

uniform vec3 dir_light_color;
uniform vec3 light_pos;
uniform vec3 cam_pos;

uniform bool shadows_enabled;

vec3 gamma_correction(vec3 color) 
{
    return pow(color, vec3(2.2));
}

vec3 calculate_normal(vec3 normal, vec3 tangent, vec3 bitangent, vec2 uv)
{
    vec3 calculated_normal = texture(tex_norm1, uv).rgb;
    calculated_normal = calculated_normal * 2.0 - 1.0;

    mat3 tbn = mat3(tangent, bitangent, normal);
    return normalize(tbn * calculated_normal);
}

float calculate_shadows(vec4 light_space_pos)
{
    // Perspective divide
    vec3 projected_coord = light_space_pos.xyz / light_space_pos.w;
    
    // Transform [-1, 1] to [0, 1] for depth
    projected_coord = projected_coord * 0.5 + 0.5;
 
	float sampled_depth = texture(shadow_map, projected_coord.xy).r; 
    
	float current_depth = projected_coord.z;
    
	vec3 normal = normalize(fs_in.normal);
    vec3 light_dir = normalize(light_pos - fs_in.world_pos);
    float bias = max(0.05 * (1.0 - dot(fs_in.normal, light_dir)), 0.005);
    
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
    vec3 test_f = texture(tex_diff1, fs_in.uv).rgb;
    vec3 diffuse_tex = gamma_correction(texture(tex_diff1, fs_in.uv).rgb);
    
    vec3 ambient_coef = 0.5 * test_f;

    //vec3 norm = normalize(fs_in.normal);
    vec3 norm = calculate_normal(fs_in.normal, fs_in.tangent, fs_in.bitangent, fs_in.uv);
   
    vec3 V = normalize(cam_pos - fs_in.world_pos);
    vec3 L = normalize(light_pos - fs_in.world_pos);

    float diff_coef = clamp(dot(norm, L), 0, 1);    
    vec3 diffuse = diff_coef * test_f;

    float specular = 0.0;      
    vec3 H = normalize(L + V);
    
    specular = pow(max(dot(norm, H), 0.0), 64.0);    
    vec3 spec = vec3(0.2) * specular * texture(tex_spec1, fs_in.uv).rgb;

    float shadows_factor = 1.0;

    vec3 final_color = (ambient_coef + diffuse + specular);
    
	frag_color = vec4(0.0, 1.0, 0.0, 1.0);    
}