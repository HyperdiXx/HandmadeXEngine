#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include <math/vec3f.h>
#include <math/vec2f.h>

#include <rendering/api/base/texture2d.h>

namespace XEngine
{
    namespace Assets
    {
#define BONES_COUNT 10

        struct V3F
        {
            vec3f pos;
        };

        struct V3F_UV2F
        {
            vec3f pos;
            vec2f uv;
        };
    
        struct V3F_UV2F_N3F_T3F_BI3F
        {
            vec3f pos;
            vec3f normal;
            vec3f tangent;
            vec3f bitangent;
            vec2f uv;
        };    

        struct StaticVertex
        {
            vec3f pos;
            vec3f normal;
            vec2f uv;
        };

        struct AnimVertex
        {
            vec3f pos;
            vec3f normal;
            vec2f uv;

            float boneIDs[BONES_COUNT] = {}; 
            float weights[BONES_COUNT] = {};
        };

        struct BPMaterialSpec
        {
            vec3f dif;
            vec3f spec;
            vec3f ambient;
            float shiness;
        };

        struct TextureWrapper
        {
            Rendering::Texture2D* texture = nullptr;
            std::string path;
            std::string type;
        };

    }
}

#endif // !VERTEX_H

