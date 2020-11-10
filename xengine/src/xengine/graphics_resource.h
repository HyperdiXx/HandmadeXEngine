#pragma once

#ifndef XENGINE_GRAPHICS_RESOURCES_H
#define XENGINE_GRAPHICS_RESOURCES_H

#ifdef GAPI_GL
    typedef uint32 GPUHandler;
#else
    Another API Stuff
#endif

#define MAX_FRAMEBUFFER_ATTACHMENTS 10
#define MAX_COLOR_FRAMEBUFFER_ATTACHMENTS 4

class GraphicsDevice;
  
struct ColRGB
{
    real32 x, y, z;

    ColRGB(real32 x_c, real32 y_c, real32 z_c) : x(x_c), y(y_c), z(z_c) {};
};

struct ColRGBA
{
    real32 x, y, z, a;

    ColRGBA() : x(0.0f), y(0.0f), z(0.0f), a(1.0f) {};
    ColRGBA(real32 x_c, real32 y_c, real32 z_c, real32 a_c) : x(x_c), y(y_c), z(z_c), a(a_c) {};
};

struct Index
{
    uint32 v1, v2, v3;
};

struct Triangle
{
    PositionNormalTBUV f1, f2, f3;

    Triangle(const PositionNormalTBUV& v0, const PositionNormalTBUV& v1, const PositionNormalTBUV& v2)
        : f1(v0), f2(v1), f3(v2) {}
};

enum class FrameBufferFlags
{
    DEPTH,
    STENCIL
};

enum class ElementType
{
    None,
    Bool,
    Int,
    Int2,
    Int3,
    Int4,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3x3,
    Mat4x4
};

enum class GPUResourceType
{
    None,
    Texture2D,
    Texture3D,
    TextureCube,
    VertexBuffer,
    IndexBuffer,
    VertexArray,
    ShaderBuffer,
    Shader,
    Framebuffer,
    Renderbuffer
};


enum class MaterialFlag
{
    None = 0,
    Depth = 1 << 1,
    Stencil = 1 << 2,
    Blend = 1 << 3
};

enum class ShaderUniformType
{
    None,
    Int,
    Boolean,
    Float,
    Vec2Uniform,
    Vec3Uniform,
    Vec4Uniform,
    Mat4x4,
    Mat3x3,
    Sampler2D,
    Sampler3D,
    SamplerCube
};

static uint32 gpu_index = 0;

class CountedHandler
{
public:
    CountedHandler() { createResource(); };
    ~CountedHandler() { destroyResource(); }
    
    CountedHandler(const CountedHandler&) = default;
    CountedHandler(CountedHandler&&) = default;

    CountedHandler& operator=(const CountedHandler&) = default;
    CountedHandler& operator=(CountedHandler&&) = default;

    void createResource()
    {
        ++isCreated;
        ++index;
    }

    void destroyResource()
    {
        --isCreated;
        --index;
    }

    void setIndex(uint32 ind) { index = ind; }
    
    inline const bool32 isValid() const { return isCreated > 0; }
    inline uint32 getIndex() const { return index; }
    
public:
    uint32 isCreated = 0;
    uint32 index = 0;
};

class RHI
{
public:    
    void setID(GPUHandler handler) { id = handler; }
    inline GPUHandler getID() const { return id; }
    inline GPUHandler &getIDRef() { return id; }
    inline const bool32 isCreated() { return id > 0; }
protected:
    GPUResourceType resource_type = GPUResourceType::None;
    GPUHandler id;
};

class Texture2DRHI : public RHI
{
public:
    Texture2DRHI() 
    {
        resource_type = GPUResourceType::Texture2D;
    }
};

class VertexBufferRHI : public RHI
{
public:
    VertexBufferRHI() 
    {
        resource_type = GPUResourceType::VertexBuffer;
    }
};

class IndexBufferRHI : public RHI
{
public:
    IndexBufferRHI()
    {
        resource_type = GPUResourceType::IndexBuffer;
    }

};

class VertexArrayRHI : public RHI
{
public:
    VertexArrayRHI()
    {
        resource_type = GPUResourceType::VertexArray;
    }
   
};

class ShaderRHI : public RHI
{
public:
    ShaderRHI()
    {
        resource_type = GPUResourceType::Shader;
    }
};

class ShaderBufferRHI : public RHI
{
public:
    ShaderBufferRHI()
    {
        resource_type = GPUResourceType::ShaderBuffer;
    }
};

class RenderbufferRHI : public RHI
{
public:
    RenderbufferRHI()
    {
        resource_type = GPUResourceType::Renderbuffer;
    }
};

class FramebufferRHI : public RHI
{
public:
    FramebufferRHI()
    {
        resource_type = GPUResourceType::Framebuffer;
    }
};

class CubemapRHI : public RHI
{
public:
    CubemapRHI()
    {
        resource_type = GPUResourceType::TextureCube;
    }
};

class Texture2D : public CountedHandler
{
public:

    inline const bool32 isValidResource() { return rhi.isCreated() && isValid(); }

    static Texture2D create(const char *path);
    static Texture2D create(uint32 width, uint32 height, PIXEL_FORMAT type, PIXEL_INTERNAL_FORMAT internal_type);

    static Texture2D create(uint32 width, uint32 height, PIXEL_FORMAT type, PIXEL_INTERNAL_FORMAT internal_type, PIXEL_TYPE plx_type, TextureSampler &sampler);
    static Texture2D create(uint32 width, uint32 height, TEXTURE_TYPE tex_type, PIXEL_FORMAT type, PIXEL_INTERNAL_FORMAT internal_type, PIXEL_TYPE plx_type, uint32 mip_count, TextureSampler &sampler);
public:
    TextureDesc desc;
    Texture2DRHI rhi;

    std::string name;
};

struct Shader : public CountedHandler
{
public:    
    Shader() {};
    
    Shader(const Shader&) = default;
    Shader& operator=(const Shader&) = default;

    void setName(const std::string & n) { name = n; }
    inline const std::string& getName() const { return name; }

    static Shader create(const char *vertex_path, const char *pixel_path);    
    static Shader create(const char *shader_path);

public:
    ShaderRHI rhi;
private:
    std::string name;
};

struct IndexBuffer : public CountedHandler
{
public:    
    static IndexBuffer create(uint32 *indices, uint32 size);
public:
    uint32 count;
    uint32 *index_data;
    Index *data;
    IndexBufferRHI rhi;
};

struct FramebufferDesc
{    
    TextureDesc attachments[MAX_COLOR_FRAMEBUFFER_ATTACHMENTS];
    TextureDesc ds;
};

struct FramebufferSpecs
{
    uint32 framebuffer_count = 1;
    uint32 width, height;
    FrameBufferFlags flags;    
};

class Renderbuffer : public CountedHandler
{
public:
    static Renderbuffer create();
public:
    RenderbufferRHI rhi;
};

class Framebuffer : public CountedHandler
{
public:
    static Framebuffer create();
    static Framebuffer create(const FramebufferDesc &desc, const FramebufferSpecs &specs);
    static Framebuffer create(Texture2D *color, Texture2D *depth);
    static Framebuffer create(Texture2D *color, const FramebufferSpecs &specs);
public:
    Texture2D tex_attachments[MAX_COLOR_FRAMEBUFFER_ATTACHMENTS + 1];
    GLenum color_attach[MAX_COLOR_FRAMEBUFFER_ATTACHMENTS];
    uint32 colorAttachCount = 0;

    Renderbuffer rb;
    FramebufferRHI rhi;
};


struct FramebufferObject
{
    Framebuffer fb;
    FramebufferDesc desc;
};

struct BufferElement
{
    ElementType type;
    uint32 size;
    uint32 offset = 0;
    std::string name; // own string impl 

    BufferElement(const std::string& name, ElementType type)
    {
        this->name = name;
        this->type = type;
        this->size = typeSizeof(type);
    }

    uint32 typeSizeof(ElementType type)
    {
        switch (type)
        {
        case ElementType::None:
            return 0;
        case ElementType::Bool:
            return 1;
        case ElementType::Int:
            return 4;
        case ElementType::Int2:
            return 4 * 2;
        case ElementType::Int3:
            return 4 * 3;
        case ElementType::Int4:
            return 4 * 4;
        case ElementType::Float:
            return 4;
        case ElementType::Float2:
            return 4 * 2;
        case ElementType::Float3:
            return 4 * 3;
        case ElementType::Float4:
            return 4 * 4;
        case ElementType::Mat3x3:
            return 4 * 9;
        case ElementType::Mat4x4:
            return 4 * 16;
        }

        return 0;
    }

    uint32 elementTypeCount()
    {
        switch (type)
        {
        case ElementType::None:
            return 0;
        case ElementType::Bool:
        case ElementType::Int:
        case ElementType::Float:
            return 1;
        case ElementType::Int2:
        case ElementType::Float2:
            return 2;
        case ElementType::Int3:
        case ElementType::Float3:
            return 3;
        case ElementType::Int4:
        case ElementType::Float4:
            return 4;
        case ElementType::Mat3x3:
            return 9;
        case ElementType::Mat4x4:
            return 16;
        }

        // Log function !!!

        return 0;
    }
};

struct BufferLayout
{
    std::vector<BufferElement> elements;
    uint32 stride = 0;
};

class VertexBuffer : public CountedHandler
{
public:
    int32 element_count;
    BufferLayout layout;
    VertexBufferRHI rhi;
    void *data;

    static VertexBuffer create(DRAW_TYPE draw_type, void *vertices, uint32 size);
};

struct TextureWrapper
{
    Texture2D *texture = nullptr;
    std::string path;
    std::string type;
};

class VertexArray : public CountedHandler
{
public:
    static VertexArray create();
public:
    std::vector<VertexBuffer*> buffers;
    IndexBuffer *ib;
    uint32 ibuffer_index = 0;
    VertexArrayRHI rhi;
};

class Cubemap : public CountedHandler
{
public:
    static Cubemap create();
public:
    CubemapRHI rhi;
    std::vector<Texture2D*> face_textures;
};


enum GeometryType
{
    QUAD_MESH = 0,
    CUBE_MESH = 1,
    MODEL_MESH = 2,
    LINE_MESH = 3,
    SPHERE_MESH = 4
};

struct GeometryMesh
{ 
    uint32 vertex_count;
    uint32 index_count;    
};

struct QuadMesh : public GeometryMesh
{
    // no CPU vb 
    GeometryType type = GeometryType::QUAD_MESH;
};

struct LineMesh : GeometryMesh
{
    VertexArray *vertex_array;

    GeometryType type = GeometryType::LINE_MESH;
};

struct SphereMesh : GeometryMesh
{
    VertexArray *vertex_array;

    GeometryType type = GeometryType::SPHERE_MESH;
};

struct CubeMesh : GeometryMesh
{
    VertexArray *vertex_array;

    GeometryType type = GeometryType::CUBE_MESH;
};

struct Character
{
    GLuint  texture_id;   
    GLuint  advance;
    Vec2i   size;
    Vec2i   bearing;
};

struct Text
{
    Texture2D *texture;
};

struct Skybox
{
    VertexArray *va;
    VertexBuffer *vb;
    Cubemap *cubemap;
};

struct ShadowMap
{
    Matrix4x4 light_projection_matrix = createMat4x4();
    uint32 width, height;    
    Framebuffer depth_fbo;
};

struct LineVertexMesh
{
    Vec3 pos;
    ColRGBA color;

    LineVertexMesh() {};
};

struct QuadVertexMesh
{
    Vec3 pos;
    ColRGBA color;

    QuadVertexMesh() {};
};

class ShaderUniformProperty
{
public:
    ShaderUniformProperty() = default;
    ShaderUniformProperty(const std::string& pr_shader) : name(pr_shader) {};
    ~ShaderUniformProperty() {};

    //ShaderUniformProperty(ShaderUniformProperty && prop);
    //ShaderUniformProperty& operator=(ShaderUniformProperty && prop);
    
    inline const std::string &getName() const { return name; }

    ShaderUniformType type = ShaderUniformType::None;
    uint32 location;
    std::string name;
    const void *value;
private:

  
};

class ShaderProperties
{
public:
    inline std::vector<ShaderUniformProperty> &getProperties() { return properties; }
private:
    std::vector<ShaderUniformProperty> properties;
};

class MaterialInstance;
class Material
{
private:
    friend class MaterialInstance;
public:
    Material() = default;
    Material(Shader *shd) : shaderRef(shd) { bind(); };

    virtual ~Material() {};

    void set(const std::string &property_name, ShaderUniformType type, const void* data);

    ShaderUniformProperty *getProperty(const std::string &name);

    void bind();
    void unbind();

    void activate();
    
    inline void addMaterialFlag(MaterialFlag flag)
    {
        flags |= (uint32)flag;
    }

    inline void removeMaterialFlag(MaterialFlag flag)
    {
        flags &= ~(uint32)flag;
    }

    inline void addTexture2D(Texture2D *tex)
    {
        textures.emplace_back(tex);
    }

    inline bool32 isDepth() const { return getFlags() & (uint32)MaterialFlag::Depth; }
    inline uint32 getFlags() const { return flags; }

    inline const std::vector<Texture2D*> *getTextures2D() { return &textures; }

    Texture2D *getTexture(uint32 index) const { return textures[index]; }
    Shader *getShader() { return shaderRef; }
private:

    void addMaterialInstance(MaterialInstance *mat_inst)
    {
        instances.insert(mat_inst);
    }

private:
    std::vector<Texture2D*> textures;
    std::unordered_set<MaterialInstance*> instances;
    ShaderProperties shaderProp = {};
    Shader *shaderRef;
    uint32 flags;
};

class MaterialInstance
{
private:
    friend class Material;
public:
    MaterialInstance(Material *material_ref);
    virtual ~MaterialInstance() {};

private:
    Material *mat_ptr;
};

class PBRMaterial : public Material
{
public:
    PBRMaterial(Shader &shd) {};
    virtual ~PBRMaterial() {};

private:
    Texture2D env_cubemap;
    Texture2D irr_map;
    Texture2D prefilter_map;
    Texture2D brdf_lut;
    Texture2D color_texture;
};

struct RenderState
{
    static constexpr uint32 max_quads_count = 20000;
    static constexpr uint32 max_quad_vert = max_quads_count * 4;
    static constexpr uint32 max_quad_indices = max_quads_count * 6;

    static constexpr uint32 max_texture_slots = 32;

    static constexpr uint32 max_line_count = 10000;
    static constexpr uint32 max_line_vert = max_line_count * 2;
    static constexpr uint32 max_line_ind = max_line_count * 6;

    uint32 draw_calls;
    uint32 quads_count;
    uint32 geometry_count;
    uint32 lines_count;
    uint32 default_line_width = 2;

    uint32 line_index_count = 0;
    uint32 quad_index_count = 0;

    VertexArray line_vertex_array;
    VertexBuffer line_vertex_buffer;

    VertexArray quad_vertex_array;
    VertexBuffer quad_vertex_buffer;

    LineVertexMesh* line_vb_base = nullptr;
    LineVertexMesh* line_vb_ptr = nullptr;

    QuadVertexMesh *quad_vb_base = nullptr;
    QuadVertexMesh *quad_vb_ptr = nullptr;

    Vec4 quad_vertex_data[4];

    std::string inputShaderColorUniformName = "u_color";
};

class GPUResourceManager
{
public:

    GPUResourceManager() { }

    void addResource(VertexBuffer vb);

    CountedHandler &getResource(uint32 index, GPUResourceType type);

private:
    GPUResourceManager(const GPUResourceManager&) = delete;
    GPUResourceManager(GPUResourceManager&&) = delete;

    GPUResourceManager& operator=(const GPUResourceManager&) = delete;
    GPUResourceManager& operator=(GPUResourceManager&&) = delete;

    bool32 isCorrectType(GPUResourceType hand, GPUResourceType type);

public:
    
    std::unordered_map<std::string, Shader> shaders;
    std::unordered_map<std::string, Texture2D> textures;
    std::map<GLchar, Character> characters_map;

    std::vector<VertexBuffer> vb_handler;
    std::vector<IndexBuffer>  ib_handler;
    std::vector<VertexArray>  va_handler;
    std::vector<Texture2D> tex2d_handler;
};

#endif
