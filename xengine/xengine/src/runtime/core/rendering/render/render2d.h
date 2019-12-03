#pragma once

#ifndef RENDER2D_H
#define RENDER2D_H

#include "render.h"

namespace XEngine
{
    namespace Rendering
    {
        class Render2d
        {
        public:
            static void init();
            static void beginScene();
            static void endScene();

            static void shutdown();

        private:

        };
    }
}
#endif // !RENDER2D_H
