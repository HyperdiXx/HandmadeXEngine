#shader vertex
#version 430 core

int indices[6] = int[](0, 1, 2, 2, 1, 3);

vec3 vertices[4] = vec3[]
(
    vec3(-1, -1, 0),
    vec3(1, -1, 0),
    vec3(-1, 1, 0),
    vec3(1, 1, 0)
);

vec2 inuv[4] = vec2[]
(
    vec2(0, 0),
    vec2(1, 0),
    vec2(0, 1),
    vec2(1, 1)
);

out vec2 uv;

void main() 
{
    int index = indices[gl_VertexID];
    
    uv = inuv[index];
    
    gl_Position = vec4(vertices[index], 1.0);
}

#shader fragment
#version 430 core

struct DirLight 
{
	vec3 direction;

	float intensity;
	vec3 lightColour;
};

struct PointLight 
{
	vec3 position;

	float intensity;
	vec3 lightColour;
	float attenuationRadius;
};

struct SpotLight 
{
	vec3 position;
	vec3 direction;

	float intensity;
	vec3 lightColour;
	float attenuationRadius;

	float cutOff;
	float outerCutOff;
};

#define MAX_DIR_LIGHTS 5
#define MAX_POINT_LIGHTS 5
#define MAX_SPOT_LIGHTS 5
const float PI = 3.14159265359;

in vec2 uv;

out vec4 frag_color;

// GBuffer
uniform sampler2D albedoSpec;
uniform sampler2D normal_texture;
uniform sampler2D special_texture;
uniform sampler2D ssao_texture;
uniform sampler2D depth_texture;

// Lighting
uniform sampler2D shadowmap;
uniform ivec4 numDirPointSpotLights;
uniform DirLight dirLights[MAX_DIR_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform vec3 viewPos;
uniform vec3 lightPos;

uniform mat4 viewInverse;
uniform mat4 projectionInverse;

uniform mat4 view;
uniform mat4 projection;

vec3 getWPFromDepthTexture()
{
	// convert to [-1, 1]
	float z = 2.0 * texture(depth_texture, uv).r - 1.0; 
	vec4 clipSpacePos = vec4(uv * 2.0 - 1.0 , z, 1.0);

    mat4 inverseView = inverse(view);
    mat4 inverseProj = inverse(projection);

	vec4 viewSpacePos = inverseProj * clipSpacePos;
	viewSpacePos /= viewSpacePos.w; // Perspective division

	vec4 worldSpacePos = inverseView * viewSpacePos;

	return worldSpacePos.xyz;
}

void main() 
{
    vec3 albedo = texture(albedoSpec, uv).rgb;
	
    // change, when wll have specular textures
    float specularSampl = texture(albedoSpec, uv).a;
    specularSampl = 0.1;

	vec3 normal = texture(normal_texture, uv).rgb;
	//float metallic = texture(special_texture, uv).r;
	//float unclampedRoughness = texture(special_texture, uv).g; // Used for indirect specular (reflections)
	//float roughness = max(unclampedRoughness, 0.04); // Used for calculations since specular highlights will be too fine, and will cause flicker
	//float materialAO = texture(special_texture, uv).b;
	//float sceneAO = texture(ssaoTexture, uv).r;
	//float ao = min(materialAO, sceneAO);

	vec3 worldPos = getWPFromDepthTexture();
    
    vec3 lightVec = normalize(lightPos - worldPos);
    vec3 viewVec = normalize(viewPos - worldPos);
	vec3 reflectionVec = reflect(-viewVec, normal);

	// Calcualte ambient IBL for both diffuse and specular
	vec3 ambient_coef = vec3(0.05);
	
    float diff_coef = clamp(dot(normal, lightVec), 0, 1);    
    vec3 diffuse = albedo * diff_coef;

    vec3 halfw = normalize(viewVec + lightVec);    
    float specular = pow(max(dot(normal, halfw), 0.0), 16.0);    
    vec3 spec_coef = vec3(0.2) * specular;

    vec3 final_color = (ambient_coef + diffuse);
	frag_color = vec4(final_color, 1.0);    
}