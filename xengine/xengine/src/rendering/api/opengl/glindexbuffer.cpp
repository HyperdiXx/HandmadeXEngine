#include "glindexbuffer.h"

#include "opengl.h"

namespace XEngine
{
    namespace Rendering
    {
        GLIndexBuffer::GLIndexBuffer(uint32 *data, uint32 size) : m_element_count(size)
        {
            glGenBuffers(1, &m_id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), data, GL_STATIC_DRAW);
        }

        GLIndexBuffer::GLIndexBuffer(std::vector<uint32> data, uint32 size)
        {
            glGenBuffers(1, &m_id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), data.begin()._Ptr, GL_STATIC_DRAW);
        }

        GLIndexBuffer::~GLIndexBuffer()
        {
            glDeleteBuffers(1, &m_id);
        }

        void GLIndexBuffer::bind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        }

        void GLIndexBuffer::unbind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

    }
}

