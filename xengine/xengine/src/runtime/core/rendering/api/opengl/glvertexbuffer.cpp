#include "glvertexbuffer.h"

#include "opengl.h"

namespace XEngine
{
    namespace Rendering
    {
        GLVertexBuffer::GLVertexBuffer(real32 *data, uint32 size) : m_element_count(size)
        {            
            glGenBuffers(1, &m_id);
            glBindBuffer(GL_ARRAY_BUFFER, m_id);
            glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
         }

        GLVertexBuffer::~GLVertexBuffer()
        {
            glDeleteBuffers(1, &m_id);
        }

        void GLVertexBuffer::bind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_id);
        }

        void GLVertexBuffer::unbind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}