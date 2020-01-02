#pragma once

#include <xenpch.h>
#include "../base/vertexbuffer.h"

namespace XEngine
{
    namespace Rendering
    {
        class GLVertexBuffer : public VertexBuffer
        {
        public:
            GLVertexBuffer(real32 *vertices, uint32 size);          
            virtual ~GLVertexBuffer();
            
            virtual void bind() const override;
            virtual void unbind() const override;

            virtual const BufferLayout& get_layout() const override { return m_layout; }
            virtual void set_layout(const BufferLayout& layout) override { m_layout = layout; };

            GLuint getElementsCount() const { return m_element_count; }
        private:
            GLuint m_id;
            GLuint m_element_count;
            BufferLayout m_layout;
        };
    }
}