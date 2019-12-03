#include "glvertexarray.h"


void XEngine::Rendering::GLVertexArray::addBuffer(GLVertexBuffer * buf, GLuint attribute)
{
    bind();
    buf->bind();
    glEnableVertexAttribArray(attribute);
    glVertexAttribPointer(attribute, buf->getElementsCount(), GL_FLOAT, GL_FALSE, 0, 0);
    buf->unbind();
    unbind();
}

void XEngine::Rendering::GLVertexArray::bind() const
{
    glBindVertexArray(mId);

}

void XEngine::Rendering::GLVertexArray::unbind() const
{
    glBindVertexArray(0);

}

