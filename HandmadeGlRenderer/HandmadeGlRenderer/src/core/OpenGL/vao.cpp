

#include "vao.h"


void addIndexBuffer(std::vector<unsigned int> indices, IndexBuffer & index)
{

}

void addVertexBuffer(VertexAO *ao, std::vector<float> values, int dimension, int row)
{
    bindVAO(ao);


}

void bindVAO(VertexAO *ao)
{
    glBindVertexArray(ao->id);

    for (int i = 0; i < ao->attribs.size(); ++i)
    {
        glEnableVertexAttribArray(ao->attribs[i]);
    }
}

void unbindVAO(VertexAO *ao)
{
    for (int i = 0; i < ao->attribs.size(); i++) {
        glDisableVertexAttribArray(ao->attribs[i]);
    }

    glBindVertexArray(0);
}
