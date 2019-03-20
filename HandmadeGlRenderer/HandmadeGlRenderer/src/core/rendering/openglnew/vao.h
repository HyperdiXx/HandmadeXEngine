#pragma once

#ifndef VERTEXARRAYOBJECT
#define VERTEXARRAYOBJECT

#include "../../../application/xenpch.h"
#include "../../types.h"


#include "IndexBuffer.h"

struct __declspec(dllexport) VertexAO
{
    std::vector<unsigned int> vboIds;
    std::vector<unsigned int> attribs;
    unsigned int id;
};

struct __declspec(dllexport) GeometryBuffer
{
    uint32 vao;
    uint32 vbo;
    float data[256];
};

class __declspec(dllexport) VAO
{
public:
    static void addIndexBuffer(std::vector<unsigned int> indices, IndexBuffer &index);
    static void addVertexBuffer(std::vector<float> values, int dimension, int row);

    static void createVertexBuffer(GeometryBuffer *geo, std::vector<float> d);
    static void createIndexBuffer();
    static void setAttribPointersFloat();

    static void bindVAO(VertexAO *ao);
    static void unbindVAO(VertexAO *ao);

    static void delGeometry(GeometryBuffer *b);
};



#endif