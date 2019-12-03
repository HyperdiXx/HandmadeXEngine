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

            GLuint getElementsCount() const { return mElementCount; }
        private:
            GLuint mID;
            GLuint mElementCount;
        };
    }
}