#shader vertex
#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 mvp;
uniform mat4 model;

uniform mat3 modelInvTransp;
uniform vec4 clipPlane;

out vec4 world_pos;
out vec3 nnormal;

void main() 
{
   gl_Position = mvp * vec4(aPos, 1.0);
   world_pos = model * vec4(aPos, 1.0);
   nnormal = normalize(modelInvTransp * aNormal);
   gl_ClipDistance[0] = dot(world_pos, clipPlane);
}

#shader pixel
#version 430 core

out vec4 frag_color;

in vec4 vertexPos;
in vec3 nnormal;

uniform mat4 viewInv;

uniform vec4 lightPosition;
uniform float lightAttenuation;
uniform vec3 lightDiffuse;
uniform vec3 lightAmbient;
uniform vec3 lightSpecular;

uniform vec3 materialSpecular;
uniform float materialShininess;

uniform sampler2D samplerTerrain;
uniform float samplerCoordDivisor;


void main()
{
   /*vec3 light_dir;
   float attenuation;

   if (lightPosition.w == 0.0f)
   {
      light_dir = normalize(vec3(lightPosition));
      attenuation = 1.0f;
   }
   else 
   {
      vec3 pos_to_light = vec3(lightPosition - vertexPos);
      float distance = length(pos_to_light);
      light_dir = normalize(pos_to_light);
      attenuation = 1.0 / (lightAttenuation * distance);
   }

   vec3 normal = normalize(Normal);

   vec2 tex_coords = vec2(vs_pos.x, vs_pos.z) / samplerCoordDivisor;
   vec3 texel = vec3(texture(samplerTerrain, tex_coords));
   vec3 diffuse = attenuation * lightDiffuse * texel *
      max(0.0, dot(normal, light_dir));

   vec3 ambient = lightAmbient * texel;

   vec3 specular;
   
   if (materialShininess == 0.0 || dot(normal, light_dir) < 0.0) 
   {
      specular = vec3(0.0, 0.0, 0.0);
   }
   else 
   {
      vec3 view_dir = normalize(vec3(viewInv * vec4(0.0, 0.0, 0.0, 1.0) - vertexPos));
      vec3 reflection_dir = reflect(-light_dir, normal);
      float shine_factor = dot(reflection_dir, view_dir);
      specular = attenuation * lightSpecular * materialSpecular *
            pow(max(0.0, shine_factor), materialShininess);
   }*/

   //FragColor = vec4(diffuse + ambient + specular, 1.0);
   frag_color = vec4(0.0, 1.0, 0.0, 1.0);
}
