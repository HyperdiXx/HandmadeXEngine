#pragma once

#ifndef RENDER2D_H
#define RENDER2D_H

#include "render.h"

namespace XEngine
{
    namespace Rendering
    {
        class Render2d : public Render
        {
        public:
            Render2d();
           
            void render_quad2D();

        private:

        };
    }
}
#endif // !RENDER2D_H
