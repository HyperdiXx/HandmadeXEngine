#include "glvertexbuffer.h"

#include "opengl.h"

namespace XEngine
{
    namespace Rendering
    {
        GLVertexBuffer::GLVertexBuffer(real32 *data, uint32 size) : mElementCount(size)
        {            
            glGenBuffers(1, &mID);
            glBindBuffer(GL_ARRAY_BUFFER, mID);
            glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
         }

        GLVertexBuffer::~GLVertexBuffer()
        {
            glDeleteBuffers(1, &mID);
        }

        void GLVertexBuffer::bind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, mID);
        }

        void GLVertexBuffer::unbind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}