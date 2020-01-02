#pragma once

#ifndef QUAD_H
#define QUAD_H

#include <math/vec3f.h>
#include <runtime/core/rendering/api/base/texture.h>
#include <runtime/core/rendering/api/base/indexbuffer.h>
#include <runtime/core/rendering/api/base/vertexbuffer.h>
#include <runtime/core/rendering/api/base/vertexarray.h>


namespace XEngine
{
    namespace Geometry
    {
        class Quad
        {
        public:
            Quad(vec3f pos) : m_pos(pos) {};
            

        private:

            vec3f m_pos;
        };
    }
}

#endif // !QUAD_H

