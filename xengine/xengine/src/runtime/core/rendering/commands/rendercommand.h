#pragma once

#include <runtime/core/rendering/api/renderAPI.h>

namespace XEngine
{
    namespace Rendering
    {
        class RenderCommand
        {
        public:
            inline static void init();
            inline static void clear();

            inline static void clearColor(real32 r, real32 g, real32 b, real32 a);
            inline static void setViewport(int32 x, int32 y, int32 width, int32 height);
        private:
            static RenderAPI* s_api;
        };
    }
}
