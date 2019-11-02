#pragma once

#ifndef VERTEXARRAYOBJECT
#define VERTEXARRAYOBJECT

#include <vector>

#include <glad/glad.h>
#include <gl/GL.h>
#include "../../../types.h"

#include "../api/opengl/indexbuffer.h"

struct VertexAO
{
    std::vector<unsigned int> vboIds;
    std::vector<unsigned int> attribs;
    unsigned int id;
};

struct GeometryBuffer
{
    uint32 vao;
    uint32 vbo;
    float data[256];
};

void addIndexBuffer(std::vector<unsigned int> indices, XEngine::Rendering::IndexBuffer &index);
void addVertexBuffer(std::vector<float> values, int dimension, int row);

void createVertexBuffer(GeometryBuffer *geo, std::vector<float> d);
void createIndexBuffer();

void bindVAO(VertexAO *ao);
void unbindVAO(VertexAO *ao);

void delGeometry(GeometryBuffer *b);


#endif