#pragma once

#ifndef QUAD_H
#define QUAD_H

#include <math/vec3f.h>
#include <runtime/core/rendering/api/base/indexbuffer.h>
#include <runtime/core/rendering/api/base/vertexbuffer.h>
#include <runtime/core/rendering/api/base/vertexarray.h>

namespace XEngine
{
    namespace Geometry
    {
        class Quad
        {
        public:
            Quad(vec3f pos) : m_pos(pos)
            {
                real32 vertices[] =
                {
                      0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
                      0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
                     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
                     -0.5f,  0.5f, 0.0f,   0.0f, 1.0f
                };

                unsigned int indices[] =
                {
                   0, 1, 3,
                   1, 2, 3
                };

                m_vertex_array = Rendering::VertexArray::create();
                m_vertex_buffer = Rendering::VertexBuffer::create(vertices, 20);
                m_index_buffer = Rendering::IndexBuffer::create(indices, 6);

                Rendering::BufferLayout buffer_layout =
                {
                    { "aPos", Rendering::ElementType::Float3  },
                    { "aUV",  Rendering::ElementType::Float2, }
                };

                m_vertex_buffer->set_layout(buffer_layout);

                m_vertex_array->add_vertex_buffer(m_vertex_buffer);
                m_vertex_array->set_index_buffer(m_index_buffer);
            };
            
            inline const Rendering::VertexArray *get_vertex_array() const { return m_vertex_array; }

        private:

            Rendering::VertexArray* m_vertex_array;
            Rendering::IndexBuffer* m_index_buffer;
            Rendering::VertexBuffer* m_vertex_buffer;

            vec3f m_pos;
        };
    }
}

#endif // !QUAD_H

