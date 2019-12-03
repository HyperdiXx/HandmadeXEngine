#pragma once

#include "glvertexbuffer.h"

namespace XEngine
{
    namespace Rendering
    {
        class GLVertexArray
        {
        public:
            GLVertexArray()
            {
                glGenVertexArrays(1, &mId);
            }

            ~GLVertexArray()
            {
                for (size_t i = 0; i < mBuffer.size(); ++i)
                {
                    delete mBuffer[i];
                }

                glDeleteVertexArrays(1, &mId);
            }

            void addBuffer(GLVertexBuffer *buf, GLuint attribute);
            void bind() const;
            void unbind() const;

        private:
            GLuint mId;
            std::vector<GLVertexBuffer*> mBuffer;
        };

    }

}
