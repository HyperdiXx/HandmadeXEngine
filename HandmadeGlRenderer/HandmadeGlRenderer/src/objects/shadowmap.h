#pragma once


#include "../core/rendering/api/opengl/framebuffero.h"

namespace XEngine
{
    namespace Rendering
    {
        class ShadowMap
        {
        public:
            ShadowMap() {};

            void init();
            void calculateMatrix();

        private:
            FrameBuffer *fb;
        };
    }
}