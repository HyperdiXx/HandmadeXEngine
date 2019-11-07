#pragma once

#include "irenderable2d.h"

namespace XEngine
{
    namespace Rendering
    {
        class Render2d
        {
        protected:
            virtual void submit(const Renderable2d* renderObj) = 0;
            virtual void flush() = 0;
        };
    }
}
