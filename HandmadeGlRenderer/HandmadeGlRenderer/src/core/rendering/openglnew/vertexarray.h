#pragma once

#include "buffer.h"

namespace XEngine
{
    namespace Rendering
    {
        class VertexArray
        {
        public:
            VertexArray()
            {
                glGenVertexArrays(1, &mId);
            }

            ~VertexArray()
            {
                for (size_t i = 0; i < mBuffer.size(); ++i)
                {
                    delete mBuffer[i];
                }

                glDeleteVertexArrays(1, &mId);
            }

            void addBuffer(VertexBuffer *buf, GLuint attribute);
            void bind() const;
            void unbind() const;

        private:
            GLuint mId;
            std::vector<VertexBuffer*> mBuffer;
        };

    }

}
