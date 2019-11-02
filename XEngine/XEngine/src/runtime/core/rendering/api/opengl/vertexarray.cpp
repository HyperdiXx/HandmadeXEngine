#include "vertexarray.h"


void XEngine::Rendering::VertexArray::addBuffer(VertexBuffer * buf, GLuint attribute)
{
    bind();
    buf->bind();
    glEnableVertexAttribArray(attribute);
    glVertexAttribPointer(attribute, buf->getElementsCount(), GL_FLOAT, GL_FALSE, 0, 0);
    buf->unbind();
    unbind();
}

void XEngine::Rendering::VertexArray::bind() const
{
    glBindVertexArray(mId);

}

void XEngine::Rendering::VertexArray::unbind() const
{
    glBindVertexArray(0);

}

