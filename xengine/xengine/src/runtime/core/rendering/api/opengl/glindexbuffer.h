#pragma once

#include <xenpch.h>
#include <runtime/types.h>

#include "../base/indexbuffer.h"

namespace XEngine
{
    namespace Rendering
    {
        class GLIndexBuffer : public IndexBuffer 
        {
        public:
            GLIndexBuffer(uint32* data, uint32 size);
            GLIndexBuffer(std::vector<uint32> data, uint32 size);

            virtual ~GLIndexBuffer();

            virtual void bind() const override;
            virtual void unbind() const override;

            GLuint getCount() const { return m_element_count; };
        private:
            GLuint m_id;
            GLuint m_element_count;
        };

    }

}