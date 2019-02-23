#pragma once

#ifndef VERTEXARRAYOBJECT
#define VERTEXARRAYOBJECT

#include <vector>

#include <glad/glad.h>
#include <gl/GL.h>


#include "IndexBuffer.h"

struct VertexAO
{
    std::vector<unsigned int> vboIds;
    std::vector<unsigned int> attribs;
    unsigned int id;
};

void addIndexBuffer(std::vector<unsigned int> indices, IndexBuffer &index);
void addVertexBuffer(std::vector<float> values, int dimension, int row);

void bindVAO(VertexAO *ao);
void unbindVAO(VertexAO *ao);


#endif