#include "glvertexarray.h"

#include <glad/glad.h>

namespace XEngine
{
    namespace Rendering
    {
        GLVertexArray::GLVertexArray()
        {
            glGenVertexArrays(1, &mId);
        }

        GLVertexArray::~GLVertexArray()
        {
            for (size_t i = 0; i < mBuffer.size(); ++i)
            {
                delete mBuffer[i];
            }

            mBuffer.clear();

            glDeleteVertexArrays(1, &mId);
        }

        void GLVertexArray::bind() const
        {
            glBindVertexArray(mId);
        }

        void GLVertexArray::unbind() const
        {
            glBindVertexArray(0);
        }

        void GLVertexArray::addVertexBuffer(const VertexBuffer *vb)
        {
            // TODO : assert

            glBindVertexArray(mId);

            if (vb != nullptr)
                vb->bind();                      
        }

        void GLVertexArray::setIndexBuffer(const IndexBuffer *ib)
        {

        }

    }
}