#pragma once

#ifndef GRAPHICS_RES_H
#define GRAPHICS_RES_H

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
    COLOR_MSAA,
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
    POINTLESS
};

struct TextureDesc
{
    TEXTURE_DIMENSION dimension;
    TEXTURE_TYPE texture_type;

    int32 width = 0;
    int32 height = 0;
    uint32 mip_level;
};

struct rasterizerState
{

};

struct BlendState
{

};

struct Viewport
{
    uint32 width = 0;
    uint32 height = 0;
    uint32 x = 0;
    uint32 y = 0;
    uint32 min_depth;
    uint32 max_depth;
};

#define BONES_COUNT 10

struct Vertex
{

};

struct PositionVertex : Vertex
{
    Vec3 pos;
};

struct PositionUVVertex : Vertex
{
    Vec3 pos;
    Vec2 uv;
};

struct PositionNormalTBUV : Vertex
{
    Vec3 pos;
    Vec3 normal;
    Vec3 tangent;
    Vec3 bitangent;
    Vec2 uv;
};

struct PositionNormalUV : Vertex
{
    Vec3 pos;
    Vec3 normal;
    Vec2 uv;
};

struct PositionNormalUVBW : Vertex
{
    Vec3 pos;
    Vec3 normal;
    Vec3 tangent;
    Vec3 bitangent;
    Vec2 uv;

    uint32 bone_ids[4] = { 0, 0, 0, 0 };
    real32 weights[4]{ 0.0f, 0.0f, 0.0f, 0.0f };

    void addBone(uint32_t boneId, real32 weight)
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
    Vec3 diff;
    Vec3 spec;
    Vec3 ambient;

    real32 shiness;
};
#endif // !GRAPHICS_RES_H

