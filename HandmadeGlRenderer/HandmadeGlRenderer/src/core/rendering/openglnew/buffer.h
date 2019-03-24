#pragma once

#include "../../../xenpch.h"

namespace XEngine
{
    namespace Rendering
    {
        class VertexBuffer
        {
        public:
            VertexBuffer(GLfloat* data, GLsizei size, GLuint componCount) : mCountElements(componCount)
            {
                glGenBuffers(1, &mID);
                glBindBuffer(GL_ARRAY_BUFFER, mID);
                glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            ~VertexBuffer()
            {
                glDeleteBuffers(1, &mID);
            }

            void bind() const;
            void unbind() const;


            GLuint getElementsCount() const
            {
                return mCountElements;
            }

        private:
            GLuint mID;
            GLuint mCountElements;

        };



    }

}