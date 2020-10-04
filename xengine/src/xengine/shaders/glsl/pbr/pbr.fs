#version 330 core

out vec4 frag_color;

in vec2 uv;
in vec3 world_pos;
in vec3 normal;
in mat3 tbn;

uniform samplerCube irradiance_map;
uniform samplerCube prefilter_map;
uniform sampler2D brdf_LUT;

uniform sampler2D albedo_map;
uniform sampler2D normal_map;
uniform sampler2D metallic_map;
uniform sampler2D roughness_map;
uniform sampler2D ao_map;

uniform vec3 light_colors[4];
uniform vec3 light_positions[4];
uniform vec3 cam_pos;

const float PI = 3.14159265359;
const float MAX_REFLECTION_LOD = 4.0;

// Constant Fresnel Factor for dielectrics
const vec3 dielectric = vec3(0.04);

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

float dist_ggx(float NdotH, float roughness)
{
    // NDF = a2 / (dot(n * h))2 * (a2 - 1.0) + 1.0

    float alpha = roughness * roughness;
    float aSqr = alpha * alpha;
    
    float NdotHSqr = NdotH * NdotH;

    float denom = (NdotHSqr * (aSqr - 1.0) + 1.0);
    
    return aSqr / max(PI * denom * denom, 0.001);
}

float geometry_schlick_ggx(float NdotV, float k)
{
    // Specular G 
    //    n * v / (n * v)(1 - k) + k
    return NdotV / NdotV * (1.0 - k) + k;
}

float geometry_smith(float dotLi, float dotLo, float roughness)
{
    float r = roughness + 1.0;
	float k = (r * r) / 8.0; 
    float ggx2 = geometry_schlick_ggx(dotLi, k);
    float ggx1 = geometry_schlick_ggx(dotLo, k);

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

vec3 approximate_specular_ibl(vec3 spec_color, float roughness, vec3 N, vec3 V)
{
    float NdotV = max(dot(N, V), 0.0);
    vec3 R = 2 * dot(V, N) * N - V;

    return R;
}

void main()
{		
    // gamma correction
    vec3 albedo = pow(texture(albedo_map, uv).rgb, vec3(2.2));
    
    float metallic = texture(metallic_map, uv).r;
    float roughness = texture(roughness_map, uv).r;
    float ao = texture(ao_map, uv).r;
       
    //vec3 N = calculate_normals();
    
    vec3 N = normalize((texture(normal_map, uv).rgb) * 2.0 - 1.0);
	N = normalize(tbn * N);

    vec3 V = normalize(cam_pos - world_pos);    
    
    float dotLo = max(0.0, dot(N, V)); 

    vec3 Lr = 2.0 * dotLo * N - V;

    vec3 F0 = mix(dielectric, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    
    for(int i = 0; i < 4; ++i) 
    {
        // radiance per light
        vec3 L = normalize(light_positions[i] - world_pos);
        vec3 H = normalize(V + L);
        
        float NdotH = max(0.0, dot(N, H));
        float NdotL = max(0.0, dot(N, L));        

        //float distance = length(light_positions[i] - world_pos);
        //float attenuation = 1.0 / (distance * distance);
        //vec3 radiance = light_colors[i] * attenuation;

        // Cook-Torrance BRDF
        vec3  F    = fresnel_schlick(F0, max(0.0, dot(H, V)));        
        float NDF  = dist_ggx(NdotH, roughness);   
        float G    = geometry_smith(NdotL, dotLo, roughness);    
        
        //vec3  nominator    = NDF * G * F;
        //float denominator  = 4 * dotLo * NdotL + 0.001; // 0.001 to prevent divide by zero.
        //vec3  specular     = nominator / denominator;
        
        vec3 kd = mix(vec3(1.0) - F, vec3(0.0), metallic);

		vec3 diffuseBRDF = kd * albedo;

		// Cook-Torrance specular microfacet BRDF.
		vec3 specularBRDF = (F * NDF * G) / max(0.00001, 4.0 * dotLo * NdotL);

		// Total contribution for this light.
		Lo += (diffuseBRDF + specularBRDF) * NdotL;
        
         // kS is equal to Fresnel
        //vec3 kS = F;
        // diff
        //vec3 kD = vec3(1.0) - kS;
        
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        //kD *= 1.0 - metallic;	                
            
       
        // add to outgoing radiance Lo
        //Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }   
    
    // ambient lighting
    vec3 irradiance = texture(irradiance_map, N).rgb;
    vec3 F = fresnel_schlick_roughness(dotLo, F0, roughness);
    
    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;	  
    
    vec3 diffuseIBL    = irradiance * albedo;

    // sample both the pre-filter map and the BRDF lut and combine them together
    // use split-sum appr as IBL spec
    
    vec3 prefiltered_color = textureLod(prefilter_map, Lr,  roughness * MAX_REFLECTION_LOD).rgb;    
    vec2 specularBRDF  = texture(brdf_LUT, vec2(dotLo, roughness)).rg;
    vec3 specularIBL = prefiltered_color * (F * specularBRDF.x + specularBRDF.y);

    vec3 ambientIBL = (kD * diffuseIBL + specularIBL) * ao;
    
    vec3 result_color = ambientIBL + Lo;

    // tonemapping
    result_color = result_color / (result_color + vec3(1.0));
    
    // gamma correction
    result_color = pow(result_color, vec3(0.4545)); 

    frag_color = vec4(result_color, 1.0);
}