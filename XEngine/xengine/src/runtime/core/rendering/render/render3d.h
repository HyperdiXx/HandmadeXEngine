#pragma once

#include "irenderable3d.h"

namespace XEngine
{
    namespace Rendering
    {
        class Render3d
        {
        protected:
            virtual void sumbit(const Renderable3d* renderObj) = 0;
            virtual void flush() = 0;
        };
    }
}
