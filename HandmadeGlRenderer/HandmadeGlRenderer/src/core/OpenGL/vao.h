#pragma once

#ifndef VERTEXARRAYOBJECT
#define VERTEXARRAYOBJECT

#include <vector>

#include <glad/glad.h>
#include <gl/GL.h>
#include "../types.h"

#include "IndexBuffer.h"

struct VertexAO
{
    std::vector<unsigned int> vboIds;
    std::vector<unsigned int> attribs;
    unsigned int id;
};

struct GeometryBuffer
{
    float *data;
    uint32 vao;
    uint32 vbo;
};

void addIndexBuffer(std::vector<unsigned int> indices, IndexBuffer &index);
void addVertexBuffer(std::vector<float> values, int dimension, int row);

void createVertexBuffer(GeometryBuffer *geo);
void createIndexBuffer();

void bindVAO(VertexAO *ao);
void unbindVAO(VertexAO *ao);
void createSkybox(GeometryBuffer* sky);
void delGeometry(GeometryBuffer *b);

#endif