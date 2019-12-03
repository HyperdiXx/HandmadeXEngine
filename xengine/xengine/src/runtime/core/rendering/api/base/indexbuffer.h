#pragma once

#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <runtime/types.h>

namespace XEngine
{
    namespace Rendering
    {
        class IndexBuffer
        {
        public:
            virtual ~IndexBuffer() = default;

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            static IndexBuffer* init(uint32* indices, uint32 size);
        private:
            int id;
        };
    }
}
#endif // !VERTEX_BUFFER_H

