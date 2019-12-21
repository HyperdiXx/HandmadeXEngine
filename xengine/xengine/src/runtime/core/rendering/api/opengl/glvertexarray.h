#pragma once

#include <xenpch.h>
#include <runtime/core/rendering/api/base/vertexarray.h>

namespace XEngine
{
    namespace Rendering
    {      
        class GLVertexArray : public VertexArray
        {
        public:
            GLVertexArray();
            virtual ~GLVertexArray();

            virtual void addVertexBuffer(const VertexBuffer *vb) override;
            virtual void setIndexBuffer(const IndexBuffer *ib) override;                      

            virtual void bind() const;
            virtual void unbind() const;

        private:
            GLuint mId;
            std::vector<VertexBuffer*> mBuffer;
        };
    }
}
