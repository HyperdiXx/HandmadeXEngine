#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include <math/vec3f.h>
#include <math/vec2f.h>

namespace XEngine
{
    namespace Assets
    {
        struct VertexStruct
        {
            vec3f pos;
            vec3f normal;
            vec3f tangent;
            vec3f bitangent;
            vec2f uv;
        };

        struct TextureStruct
        {
            uint32 id;
            std::string path;
            std::string type;
        };

        struct BPMaterialSpec
        {
            vec3f dif;
            vec3f spec;
            vec3f ambient;
            float shiness;
        };

    }
}

#endif // !VERTEX_H

