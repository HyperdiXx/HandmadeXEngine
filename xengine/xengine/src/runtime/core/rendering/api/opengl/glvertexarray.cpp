#include "glvertexarray.h"

#include <glad/glad.h>

namespace XEngine
{
    namespace Rendering
    {
        GLVertexArray::GLVertexArray()
        {
            glGenVertexArrays(1, &m_id);
        }

        GLVertexArray::~GLVertexArray()
        {
            for (size_t i = 0; i < m_buffer.size(); ++i)
            {
                delete m_buffer[i];
            }

            m_buffer.clear();

            glDeleteVertexArrays(1, &m_id);
        }

        void GLVertexArray::bind() const
        {
            glBindVertexArray(m_id);
        }

        void GLVertexArray::unbind() const
        {
            glBindVertexArray(0);
        }

        void GLVertexArray::add_vertex_buffer(VertexBuffer *vb)
        {
            // TODO : assert

            glBindVertexArray(m_id);
            if (vb != nullptr)
                vb->bind();         

            const auto& buffer_layout = vb->get_layout();

            for (uint16 i = 0; i < buffer_layout.get_elements().size(); i++)
            {
                auto cur_element = buffer_layout.get_elements().at(i);
                glEnableVertexAttribArray(m_ibuffer_index);
                glVertexAttribPointer(m_ibuffer_index, cur_element.element_type_count(), GL_FLOAT, GL_FALSE, buffer_layout.get_stride(), (void*)cur_element.m_offset);
                m_ibuffer_index++;
            }

            m_buffer.push_back(vb);
        }

        void GLVertexArray::set_index_buffer(IndexBuffer *ib)
        {
            // assert 
            if (ib != nullptr)
            {
                glBindVertexArray(m_id);
                ib->bind();

                m_ib = ib;
            }
                
        }

    }
}