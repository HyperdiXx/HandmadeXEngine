#pragma once


#pragma comment(lib, "d3d11.lib")		
#pragma comment(lib, "dxgi.lib")		
#pragma comment(lib, "d3dcompiler.lib")	

#include <d3d11.h>


enum class DXRasterizerCullMode
{
    FRONT = D3D11_CULL_FRONT,
    NONE = D3D11_CULL_NONE,
    BACK = D3D11_CULL_BACK,

    WIREFRAME = D3D11_FILL_WIREFRAME,
};

enum class DXRasterizerFillMode
{
    SOLID = D3D11_FILL_SOLID,
    WIREFRAME = D3D11_FILL_WIREFRAME,
};

enum class DXPrimitiveTopology
{
    POINT_LIST = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
    TRIANGLE_LIST = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
    LINE_LIST = D3D11_PRIMITIVE_TOPOLOGY_LINELIST,

    TOPOLOGY_COUNT
};


enum DXDefaultRasterizerState
{
    // FILL
    CULL_NONE = 0,
    CULL_FRONT,
    CULL_BACK,

    // WIREFRAME
    WIREFRAME,

    RASTERIZER_STATE_COUNT
};

enum DXDefaultBlendState
{
    DISABLED,
    ADDITIVE_COLOR,
    ALPHA_BLEND,

    BLEND_STATE_COUNT
};

enum DXDefaultSamplerState
{
    POINT_SAMPLER,
    LINEAR_FILTER_SAMPLER_WRAP_UVW,
    LINEAR_FILTER_SAMPLER,
    WRAP_SAMPLER,

    DEFAULT_SAMPLER_COUNT
};


enum DXDefaultDepthStencilState
{
    DEPTH_STENCIL_WRITE,
    DEPTH_STENCIL_DISABLED,
    DEPTH_WRITE,
    STENCIL_WRITE,
    DEPTH_TEST_ONLY,
   
    DEPTH_STENCIL_STATE_COUNT
};

enum DXLayoutFormat
{
    FLOAT32_2 = DXGI_FORMAT_R32G32_FLOAT,
    FLOAT32_3 = DXGI_FORMAT_R32G32B32_FLOAT,
    FLOAT32_4 = DXGI_FORMAT_R32G32B32A32_FLOAT,

    LAYOUT_FORMAT_COUNT
};

enum DXTextureUsage : unsigned
{
    RESOURCE = D3D11_BIND_SHADER_RESOURCE,
    RENDER_TARGET = D3D11_BIND_RENDER_TARGET,
    RENDER_TARGET_RW = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET,
    DEPTH_TARGET = D3D11_BIND_DEPTH_STENCIL,
    COMPUTE_RW_TEXTURE = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE,

    TEXTURE_USAGE_COUNT
};

enum DXCPUAccess : unsigned
{
    NONE = 0,
    CPU_R = D3D11_CPU_ACCESS_READ,
    CPU_W = D3D11_CPU_ACCESS_WRITE,
    CPU_RW = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE
};

enum DXImageFormat
{
    // RGBA
    RGBA32F = DXGI_FORMAT_R32G32B32A32_FLOAT,
    RGBA16F = DXGI_FORMAT_R16G16B16A16_FLOAT,
    RGBA8UN = DXGI_FORMAT_R8G8B8A8_UNORM,

    // RGB
    RGB32F = DXGI_FORMAT_R32G32B32_FLOAT,

    // RG
    RG32F = DXGI_FORMAT_R32G32_FLOAT,
    RG16F = DXGI_FORMAT_R16G16_FLOAT,

    // R
    R32F = DXGI_FORMAT_R32_FLOAT,
    R32U = DXGI_FORMAT_R32_UINT,

    R8U = DXGI_FORMAT_R8_UINT,
    R8UN = DXGI_FORMAT_R8_UNORM,

    // Typeless
    R32 = DXGI_FORMAT_R32_TYPELESS,
    R24G8 = DXGI_FORMAT_R24G8_TYPELESS,

    // 
    R24_UNORM_X8_TYPELESS = DXGI_FORMAT_R24_UNORM_X8_TYPELESS,

    // Depth
    D32F = DXGI_FORMAT_D32_FLOAT,
    D24UNORM_S8U = DXGI_FORMAT_D24_UNORM_S8_UINT,

    IMAGE_FORMAT_UNKNOWN,
    IMAGE_FORMAT_COUNT
};



enum EGeometry
{
    TRIANGLE = 0,
    QUAD,
    FULLSCREENQUAD,
    CUBE,
    CYLINDER,
    SPHERE,
    GRID,
    //BONE,

    MESH_TYPE_COUNT
};

enum EShaders : unsigned	
{
    FORWARD_PHONG = 0,
    UNLIT,
    TEXTURE_COORDINATES,
    NORMAL,
    TANGENT,
    BINORMAL,
    LINE,
    TBN,
    DEBUG,
    SKYBOX,
    SKYBOX_EQUIRECTANGULAR,
    FORWARD_BRDF,
    SHADOWMAP_DEPTH,
    DEFERRED_GEOMETRY = SHADOWMAP_DEPTH + 7,	
    SHADER_COUNT
};

enum EShaderStageFlags : unsigned
{
    SHADER_STAGE_NONE = 0x00000000,
    SHADER_STAGE_VS = 0x00000001,
    SHADER_STAGE_GS = 0x00000002,
    SHADER_STAGE_DS = 0x00000004,
    SHADER_STAGE_HS = 0x00000008,
    SHADER_STAGE_PS = 0x00000010,
    SHADER_STAGE_ALL_GRAPHICS = 0X0000001F,
    SHADER_STAGE_CS = 0x00000020,

    SHADER_STAGE_COUNT = 6
};

enum DXShaderStage : unsigned	
{	
    VS = 0,
    GS,
    DS,
    HS,
    PS,
    CS,

    COUNT
};

enum DXBufferUsage
{	
    GPU_READ = D3D11_USAGE_IMMUTABLE,
    GPU_READ_WRITE = D3D11_USAGE_DEFAULT,
    GPU_READ_CPU_WRITE = D3D11_USAGE_DYNAMIC,
    GPU_READ_CPU_READ = D3D11_USAGE_STAGING,

    BUFFER_USAGE_COUNT
};

enum DXBufferType : unsigned
{
    VERTEX_BUFER = D3D11_BIND_VERTEX_BUFFER,
    INDEX_BUFFER = D3D11_BIND_INDEX_BUFFER,
    // CONSTANT_BUFFER, // this can fit here
    COMPUTE_RW_BUFFER = D3D11_BIND_UNORDERED_ACCESS,
    //	COMPUTE_RW_TEXTURE = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE,

    BUFFER_TYPE_UNKNOWN,
    BUFFER_TYPE_COUNT
};

enum DXMaterialType
{
    GGX_BRDF = 0,
    BLINN_PHONG,

    MATERIAL_TYPE_COUNT
};