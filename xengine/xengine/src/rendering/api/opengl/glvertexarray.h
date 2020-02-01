#pragma once

#include <xenpch.h>
#include <rendering/api/base/vertexarray.h>

namespace XEngine
{
    namespace Rendering
    {      
        class GLVertexArray : public VertexArray
        {
        public:
            GLVertexArray();
            virtual ~GLVertexArray();

            virtual void add_vertex_buffer(VertexBuffer *vb) override;
            virtual void set_index_buffer(IndexBuffer *ib) override;                      

            virtual void bind() const;
            virtual void unbind() const;             
        private:
            GLuint m_id;
            uint32 m_ibuffer_index = 0;
            std::vector<VertexBuffer*> m_buffer;
            IndexBuffer *m_ib;
        };
    }
}
