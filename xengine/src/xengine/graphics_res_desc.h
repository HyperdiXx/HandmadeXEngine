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
    PS,
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
    DEPTH,
    STENCIL,
    DEPTH_STENCIL
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

enum API_TYPE
{
    OPENGL,
    VULKAN,
    DX11
};

enum PIXEL_FORMAT
{
    RGBA8,
    RGBA16,
    RGBA8F,
    RGBA16F,
    Depth24,
    Depth32,
    Stencil24,
    Stencil32,
    DepthStencil32
};

enum PIXEL_TYPE
{
    PTUBYTE,
    PTUSHORT,    
    PTUINT,    
    PTFLOAT
};

enum PIXEL_INTERNAL_FORMAT
{
    IFRGB,
    IFRGBA,
    IFDEPTH,
    IFDEPTHSTENCIL,
    IFRG,
    IFR
};

enum RENDER_TARGET_TYPE
{
    RTColor0,
    RTColor1,
    RTColor2,
    RTColor3,
    RTDepth,
    RTStencil,
    RTDepthStencil
};

struct TextureSampler
{
    TEXTURE_SAMPLING pxl_sampling_min;
    TEXTURE_SAMPLING pxl_sampling_mag;
    
    TEXTURE_WRAPPING wrapping_s;
    TEXTURE_WRAPPING wrapping_t;
    TEXTURE_WRAPPING wrapping_r;
};

struct TextureDesc
{
    TEXTURE_DIMENSION dimension;
    TEXTURE_TYPE texture_type;
    PIXEL_FORMAT pixel_format;
    PIXEL_INTERNAL_FORMAT internal_pixel_format;
    PIXEL_TYPE pxl_type;

    TextureSampler sampler;
    int32 width = 0;
    int32 height = 0;
    uint32 mip_count;
};

struct RasterizerState
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

