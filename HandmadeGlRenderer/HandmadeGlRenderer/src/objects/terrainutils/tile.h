#pragma once

#ifndef TERRAINTILEH
#define TERRAINTILE

#include "../../xenpch.h"
#include "../../core/types.h"

namespace XEngine
{
    namespace Terrain
    {
        class Tile
        {
        public:

            void init(uint32 w, uint32 h, real32 x, real32 y, uint32 tex);
            void render();

            void bind();

        private:

            uint32 width, height;

            glm::vec3 pos;
            glm::vec3 rot;
            glm::vec3 scale;

            glm::vec2 vertices[6];
            glm::vec2 uv[6];

            uint32 texture;

            unsigned vao;
            unsigned vertex_buf;
            unsigned uv_buffer;

        };

    }
}

#endif
