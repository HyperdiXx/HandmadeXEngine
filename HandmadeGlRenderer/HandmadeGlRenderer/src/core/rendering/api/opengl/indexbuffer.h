#pragma once


#include "../../../../xenpch.h"

namespace XEngine
{
    namespace Rendering
    {
        class IndexBuffer
        {
        public:
            IndexBuffer(GLuint* data, GLsizei size) : mCount(size)
            {
                glGenBuffers(1, &mID);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), data, GL_STATIC_DRAW);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }

            ~IndexBuffer()
            {
                glDeleteBuffers(1, &mID);
            }

            void bind() const;
            void unbind() const;

            GLuint getCount() const { return mCount; };
        private:
            GLuint mID;
            GLuint mCount;
        };

    }

}