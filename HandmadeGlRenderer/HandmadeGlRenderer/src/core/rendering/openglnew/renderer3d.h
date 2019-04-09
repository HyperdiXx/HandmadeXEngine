#pragma once

#include <deque>

#include "render3d.h"


namespace XEngine
{
    namespace Rendering
    {
        class Renderer3d : Render3d
        {
        public:
            void submit(const Renderable3d* renderObj);
            void flush();
        private:
            std::deque<int> mRenderQ;
        };
    }
}
