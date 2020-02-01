#pragma once

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "vertexbuffer.h"
#include "indexbuffer.h"

namespace XEngine
{
    namespace Rendering
    {        
        class VertexArray
        {
        public:
            virtual ~VertexArray() = default;

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual void add_vertex_buffer(VertexBuffer *vb) = 0;
            virtual void set_index_buffer(IndexBuffer *ib) = 0;

            static VertexArray* create();
        };
    }
}
#endif // !VERTEXARRAY_H

