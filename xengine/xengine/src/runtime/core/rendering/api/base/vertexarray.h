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

            virtual void addVertexBuffer(const VertexBuffer *vb) = 0;
            virtual void setIndexBuffer(const IndexBuffer *ib) = 0;

            static VertexArray* create();
        };
    }
}
#endif // !VERTEXARRAY_H

