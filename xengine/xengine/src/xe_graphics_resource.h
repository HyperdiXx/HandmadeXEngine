#pragma once

#ifndef XENGINE_GRAPHICS_RESOURCES_H
#define XENGINE_GRAPHICS_RESOURCES_H

#include "xenpch.h"
#include "xe_graphics_res_desc.h"

#include "xe_config.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace xe_graphics
{
#ifdef GAPI_GL
    typedef uint32 GPUHandler;
#else
    Another API Stuff
#endif

    class GraphicsDevice;

    struct Color3RGB
    {
        real32 x, y, z;

        Color3RGB(real32 x_c, real32 y_c, real32 z_c) : x(x_c), y(y_c), z(z_c) {};
    };

    struct Color4RGBA
    {
        real32 x, y, z, a;

        Color4RGBA() : x(0.0f), y(0.0f), z(0.0f), a(1.0f) {};
        Color4RGBA(real32 x_c, real32 y_c, real32 z_c, real32 a_c) : x(x_c), y(y_c), z(z_c), a(a_c) {};
    };

    struct Texture2D
    {
        GPUHandler id;
        bool32 is_valid;
        TextureDesc desc;
    };

    struct Shader
    {
        GPUHandler id;
    };
   
    struct Index
    {
        GPUHandler v1, v2, v3;
    };

    struct IndexBuffer
    {
        GPUHandler id;
        GPUHandler count;
        GPUHandler *index_data;
        Index *data;
    };

    struct Framebuffer
    {
        GPUHandler fbo_id;
        GPUHandler rb_id;
        std::vector<Texture2D*> color_textures;
        Texture2D *depth_texture;
        Texture2D *stencil_texture;
        std::vector<GLenum> buffers;
    };

    enum ElementType
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

    struct BufferElement
    {
        std::string name; // own string impl 
        ElementType type;
        GPUHandler size;
        GPUHandler offset = 0;
        
        BufferElement(const std::string& name , ElementType type)
        {
            this->name = name;
            this->type = type;
            this->size = typeSizeof(type);
        }

        GPUHandler typeSizeof(ElementType type)
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

        GPUHandler elementTypeCount()
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
        GPUHandler stride = 0;
    };

    struct VertexBuffer
    {
        GPUHandler id;
        GPUHandler element_count;
        BufferLayout layout;
        void *data;
    };
   
    struct TextureWrapper
    {
        Texture2D *texture = nullptr;
        std::string path;
        std::string type;
    };

    struct VertexArray
    {
        GPUHandler id;
        GPUHandler ibuffer_index = 0;
        std::vector<VertexBuffer*> buffers;
        IndexBuffer *ib;
    };

    struct QuadMesh
    {
        GPUHandler vertex_count;
        glm::vec3 color;
        glm::vec2 uv;
    };

    struct LineMesh
    {
        GPUHandler vertex_count;        
        xe_graphics::VertexArray *va;
        glm::vec3 color;
    };

    struct SphereMesh
    {
        xe_graphics::VertexArray *vertex_array;
    };

    struct CubeMesh
    {
        xe_graphics::VertexArray *vertex_array;
    };

    struct Character
    {
        GLuint     texture_id;
        glm::ivec2 size;
        glm::ivec2 bearing;
        GLuint     advance;
    };

    struct Text
    {
        Texture2D *texture;
    };

    struct Cubemap
    {
        GPUHandler id;
        std::vector<Texture2D*> face_textures;
    };

    struct Skybox
    {
        VertexArray *va;
        VertexBuffer *vb;
        Cubemap *cubemap;
    };

    struct ShadowMap
    {
        uint32 width_map, height_map;
        glm::mat4 light_projection_matrix = glm::mat4(1.0f);
        Framebuffer depth_fbo;
    };

    struct LineVertexMesh
    {
        glm::vec3 pos;
        Color4RGBA color; 

        LineVertexMesh() {};
    };

    struct QuadVertexMesh
    {
        glm::vec3 pos;
        Color4RGBA color;

        QuadVertexMesh() {};
    };

    enum class MaterialFlag
    {
        None = 0,
        Depth = 1 << 1,
        Stencil = 1 << 2, 
        Blend = 1 << 3
    };

    class ShaderProperty
    {
    public:       
        ShaderProperty() = default;
        ShaderProperty(const std::string& name) : property_name(name) {};
        ~ShaderProperty() {};
    
        inline const std::string &getName() const { return property_name; }
    
    private:
        std::string property_name;
    };

    class ShaderProperties
    {
    public:

        inline const std::vector<ShaderProperty> &getProperties() const { return properties; }

    private:
        std::vector<ShaderProperty> properties;
    };

    class MaterialInstance;
    class Material
    {
    private:
        friend class MaterialInstance;
    public:     
        Material() = default;
        Material(Shader *shd) : shaderRef(shd) {};
        
        virtual ~Material() {};

        template<typename T>
        void set(const std::string &property_name, const T &value)
        {
            auto &definitions = shaderProp.getProperties();

            

        };

        

    private:
        std::unordered_set<MaterialInstance*> instances;
        Shader *shaderRef;
        ShaderProperties shaderProp = {};

        std::vector<Texture2D*> textures;
        uint32 flags;
    };

    class MaterialInstance
    {
    private:
        friend class Material;
    public:
        MaterialInstance(const Material &material_ref) {};
        virtual ~MaterialInstance() {};
    
    private:

    };

    class PBRMaterial : public Material
    {
    public:
        PBRMaterial(Shader &shd) {};
        virtual ~PBRMaterial() {};

    private:
        xe_graphics::Texture2D env_cubemap;
        xe_graphics::Texture2D irr_map;
        xe_graphics::Texture2D prefilter_map;
        xe_graphics::Texture2D brdf_lut;
        xe_graphics::Texture2D color_texture;
    };

    struct Triangle
    {
        PositionNormalTBUV f1, f2, f3;

        Triangle(const PositionNormalTBUV& v0, const PositionNormalTBUV& v1, const PositionNormalTBUV& v2)
            : f1(v0), f2(v1), f3(v2) {}
    };

    struct RenderState
    {
        static const uint32 max_quads_count = 20000;
        static const uint32 max_quad_vert = max_quads_count * 4;
        static const uint32 max_quad_indices = max_quads_count * 6;

        static const uint32 max_texture_slots = 32;

        static const uint32 max_line_count = 10000;
        static const uint32 max_line_vert = max_line_count * 2;
        static const uint32 max_line_ind = max_line_count * 6;

        GPUHandler draw_calls;
        GPUHandler quads_count;
        GPUHandler geometry_count;
        GPUHandler lines_count;
        GPUHandler default_line_width = 2;

        std::string inputShaderColorUniformName = "u_color";

        VertexArray line_vertex_array;
        VertexBuffer line_vertex_buffer;

        VertexArray quad_vertex_array;
        VertexBuffer quad_vertex_buffer;

        GPUHandler line_index_count = 0;
        LineVertexMesh* line_vb_base = nullptr;
        LineVertexMesh* line_vb_ptr = nullptr;

        GPUHandler quad_index_count = 0;
        QuadVertexMesh *quad_vb_base = nullptr;
        QuadVertexMesh *quad_vb_ptr = nullptr;

        glm::vec4 quad_vertex_data[4];
    };
}
#endif
