#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include <math/vec2f.h>
#include <math/vec3f.h>
#include <types.h>

struct Vertex
{
    vec3f pos;
    vec2f uv;
    uint32 color;
};

static Vertex getP3F()
{
    Vertex a = {};
    return a;
}




#endif // !VERTEX_H

