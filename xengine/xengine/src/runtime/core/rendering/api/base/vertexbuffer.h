#pragma once

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <runtime/types.h>

namespace XEngine
{
    namespace Rendering
    {
        class VertexBuffer
        {
        public:
            virtual ~VertexBuffer() = default;

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            static VertexBuffer* create(real32* vertices, uint32 size);
        };
    }
}

#endif // !VERTEXBUFFER_H
