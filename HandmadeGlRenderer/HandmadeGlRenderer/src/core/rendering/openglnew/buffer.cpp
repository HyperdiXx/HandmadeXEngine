#include "buffer.h"


namespace XEngine
{
    namespace Rendering
    {

        
        void VertexBuffer::bind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, mID);
        }
        void VertexBuffer::unbind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }


    }
}