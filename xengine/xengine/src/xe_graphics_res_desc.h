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

    enum BUFFER_TYPE
    {
        VERTEX,
        INDEX
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
        LUT, 
        CUBEMAP, 
        CUBEMAP_POSITIVE, 
        DEPTH
    };

    enum TEXTURE_WRAPPING
    {       
        TEXTURE_ADDRESS_REPEAT,
        TEXTURE_ADDRESS_MIR_REPEAT,
        TEXTURE_ADDRESS_CLAMP,
        TEXTURE_ADDRESS_BORDER
    };

    enum TEXTURE_WRAPPING_AXIS
    {
        TEXTURE_AXIS_S,
        TEXTURE_AXIS_T,
        TEXTURE_AXIS_R
    };

    enum TEXTURE_SAMPLING
    {
        LINEAR,
        NEAREST, 
        NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_LINEAR
    };

    enum TEXTURE_FILTER_OPERATION
    {
        MIN,
        MAG
    };
    
    enum TEXTURE_DIMENSION
    {
        TEXTURE_2D,
        TEXTURE_1D,
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
        TEXTURE_DIMENSION dimension;
        TEXTURE_TYPE texture_type;

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

    struct vertex
    {

    };

    struct position_vertex : vertex
    {
        vec3f pos;
    };

    struct position_uv_vertex : vertex
    {
        vec3f pos;
        vec2f uv;
    };

    struct pos_normal_tb_uv : vertex
    {
        vec3f pos;
        vec3f normal;
        vec3f tangent;
        vec3f bitangent;
        vec2f uv;
    };

    struct pos_normal_uv : vertex
    {
        vec3f pos;
        vec3f normal;
        vec2f uv;
    };

    struct pos_normal_uv_b_w : vertex
    {
        vec3f pos;
        vec3f normal;
        vec3f tangent;
        vec3f bitangent;
        vec2f uv;

        uint32 bone_ids[4] = { 0, 0, 0, 0 };
        real32 weights[4]{ 0.0f, 0.0f, 0.0f, 0.0f };

        void add_bone(uint32_t boneId, real32 weight)
        {
            for (uint32_t size = 0; size < 4; size++)
            {
                if (weights[size] == 0.0f)
                {
                    bone_ids[size] = boneId;
                    weights[size] = weight;
                    return;
                }
            }
        }
    };

    struct BPMaterialSpec
    {
        vec3f diff;
        vec3f spec;
        vec3f ambient;

        real32 shiness;
    };
}
