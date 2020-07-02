#pragma once

#ifndef XENGINE_GRAPHICS_RESOURCES_H
#define XENGINE_GRAPHICS_RESOURCES_H

#include "xe_graphics_res_desc.h"

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace xe_graphics
{
    class GraphicsDevice;

    struct Texture2D
    {
        uint32 id;
        bool32 is_valid;
        TextureDesc desc;
    };

    struct Shader
    {
        uint32 id;
    };
   
    struct IndexBuffer
    {
        uint32 id;
        uint32 count;
        uint32 *data;
    };

    struct Framebuffer
    {
        uint32 fbo_id;
        uint32 rb_id;
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
        uint32 size;
        uint32 offset = 0;
        
        BufferElement(const std::string& name , ElementType type)
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

    struct VertexBuffer
    {
        uint32 id;
        uint32 element_count;
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
        uint32 id;
        uint32 ibuffer_index = 0;
        std::vector<VertexBuffer*> buffers;
        IndexBuffer *ib;
    };

    struct Quad
    {
        Quad() {};
        Quad(int xPos, int yPos, int wi, int he) : x(xPos), y(yPos), w(wi), h(he) {};

        int x, y, w, h;
        xe_graphics::VertexArray *vertex_array;
    };

    struct Line
    {
        uint32 vertex_count;        
        xe_graphics::VertexArray *va;
        glm::vec3 color;
    };

    struct Sphere
    {
        xe_graphics::VertexArray *vertex_array;
    };

    struct Cube
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
        Quad *q;
        Texture2D *texture;
    };

    struct Cubemap
    {
        uint32 id;
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
        uint32 w;
        uint32 h;
        glm::mat4 light_projection_matrix = glm::mat4(1.0f);
        Framebuffer depth_fbo;
    };
}
#endif
