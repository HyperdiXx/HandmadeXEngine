#pragma once

#include <types.h>

#include <math/vec3f.h>
#include <math/vec2f.h>

namespace xe_graphics
{
    enum DRAW_TYPE
    {
        NONE,
        STATIC,
        DYNAMIC
    };

    enum SHADER_TYPE
    {
        VS,
        FS,
        GS,
        HS,
        CS
    };

    enum TEXTURE_TYPE
    {
        COLOR, 
        HDR, 
        GREYSCALE,
        LUT
    };

    enum TEXTURE_WRAPPING
    {       
        TEXTURE_ADDRESS_REPEAT,
        TEXTURE_ADDRESS_WRAP,
        TEXTURE_ADDRESS_CLAMP,
        TEXTURE_ADDRESS_BORDER,
    };

    enum TEXTURE_SAMPLING
    {
        LINEAR,
        REPEAT
    };

    enum TEXTURE_DIMENSION
    {
        TEXTURE_1D,
        TEXTURE_2D,
        TEXTURE_3D
    };

    enum PRIMITIVE_TOPOLOGY
    {
        TRIANGLE,
        TRIANGLE_STRIP,
        LINE,
        LINE_LOOP,
        LINE_STRIP,
        POINT
    };

    struct texture_desc
    {
        TEXTURE_DIMENSION type;

        int32 width = 0;
        int32 height = 0;
        uint32 mip_level;
    };

    struct rasterizer_state
    {

    };

    struct blend_state
    {

    };

    struct viewport
    {
        uint32 width = 0;
        uint32 height = 0;
        uint32 x = 0;
        uint32 y = 0;
        uint32 min_depth;
        uint32 max_depth;
    };

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

    struct static_vertex
    {
        vec3f pos;
        vec3f normal;
        vec2f uv;
    };

    struct anim_vertex
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
}
