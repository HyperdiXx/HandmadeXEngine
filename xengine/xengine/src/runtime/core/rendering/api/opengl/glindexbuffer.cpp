#include "glindexbuffer.h"

#include "opengl.h"

namespace XEngine
{
    namespace Rendering
    {
        GLIndexBuffer::GLIndexBuffer(uint32 * data, uint32 size) : mElementCount(size)
        {
            glGenBuffers(1, &mID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), data, GL_STATIC_DRAW);
        }

        GLIndexBuffer::~GLIndexBuffer()
        {
            glDeleteBuffers(1, &mID);
        }

        void GLIndexBuffer::bind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
        }

        void GLIndexBuffer::unbind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

    }
}

