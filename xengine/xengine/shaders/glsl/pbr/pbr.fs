#version 330 core
out vec4 frag_color;

in vec2 uv;
in vec3 world_pos;
in vec3 normal;

uniform sampler2D albedo_map;
uniform sampler2D normal_map;
uniform sampler2D metallic_map;
uniform sampler2D roughness_map;
uniform sampler2D ao_map;

// IBL
uniform samplerCube irradiance_map;
uniform samplerCube prefilter_map;
uniform sampler2D brdf_LUT;

uniform vec3 light_colors[4];
uniform vec3 light_positions[4];
uniform vec3 cam_pos;

const float PI = 3.14159265359;

// Constant Fresnel Factor for dielectrics
vec3 F0 = vec3(0.04);

vec3 calculate_normals()
{
    vec3 tangent_space_normal = texture(normal_map, uv).xyz;
    tangent_space_normal = tangent_space_normal * 2.0 - 1.0;

    vec3 Q1  = dFdx(world_pos);
    vec3 Q2  = dFdy(world_pos);
    vec2 st1 = dFdx(uv);
    vec2 st2 = dFdy(uv);

    vec3 N   = normalize(normal);
    vec3 T   = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B   = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangent_space_normal);
}

float dist_ggx(vec3 N, vec3 H, float roughness)
{
    float alpha = roughness * roughness;
    float aSqr = alpha * alpha;
    float NdotH = max(dot(N, H), 0.0);
    float NdotHSqr = NdotH * NdotH;

    float denom = (NdotHSqr * (aSqr - 1.0) + 1.0);
    
    return aSqr / max(PI * denom * denom, 0.001);
}

float geometry_schlick_ggx(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    return NdotV / NdotV * (1.0 - k) + k;
}

float geometry_smith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = geometry_schlick_ggx(NdotV, roughness);
    float ggx1 = geometry_schlick_ggx(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 fresnel_schlick(vec3 F0, float cosTheta)
{
    return F0 + (vec3(1.0) - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 fresnel_schlick_roughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}   

void main()
{		
    // gamma correction
    vec3 albedo = pow(texture(albedo_map, uv).rgb, vec3(2.2));
    
    float metallic = texture(metallic_map, uv).r;
    float roughness = texture(roughness_map, uv).r;
    float ao = texture(ao_map, uv).r;
       
    vec3 N = calculate_normals();
    vec3 V = normalize(cam_pos - world_pos);    
    vec3 R = reflect(-V, N); 
    
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    
    for(int i = 0; i < 4; ++i) 
    {
        // radiance per light
        vec3 L = normalize(light_positions[i] - world_pos);
        vec3 H = normalize(V + L);
        
        float distance = length(light_positions[i] - world_pos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = light_colors[i] * attenuation;

        // Cook-Torrance BRDF
        float NDF = dist_ggx(N, H, roughness);   
        float G   = geometry_smith(N, V, L, roughness);    
        vec3 F    = fresnel_schlick(F0, max(dot(H, V), 0.0));        
        
        vec3  nominator    = NDF * G * F;
        float denominator  = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 to prevent divide by zero.
        vec3  specular     = nominator / denominator;
        
         // kS is equal to Fresnel
        vec3 kS = F;
        // diff
        vec3 kD = vec3(1.0) - kS;
        
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;	                
            
        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);        

        // add to outgoing radiance Lo
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }   
    
    // ambient lighting
    vec3 F = fresnel_schlick_roughness(max(dot(N, V), 0.0), F0, roughness);
    
    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;	  
    
    vec3 irradiance = texture(irradiance_map, N).rgb;
    vec3 diffuse    = irradiance * albedo;
    
    // sample both the pre-filter map and the BRDF lut and combine them together as per the Split-Sum approximation to get the IBL specular part.
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefiltered_color = textureLod(prefilter_map, R,  roughness * MAX_REFLECTION_LOD).rgb;    
    vec2 brdf  = texture(brdf_LUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
    vec3 specular = prefiltered_color * (F * brdf.x + brdf.y);

    vec3 ambient = (kD * diffuse + specular) * ao;
    
    vec3 result_color = ambient + Lo;

    // Tonemapping
    result_color = result_color / (result_color + vec3(1.0));
    
    // Gamma correction
    result_color = pow(result_color, vec3(1.0/2.2)); 

    frag_color = vec4(result_color , 1.0);
}