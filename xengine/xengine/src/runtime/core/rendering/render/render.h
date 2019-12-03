#pragma once

#include "renderable2d.h"
#include <runtime/core/rendering/api/renderAPI.h>

namespace XEngine
{
    namespace Rendering
    {
        class Render
        {
        public:
            static void init();

            static void beginScene();
            static void endScene();

            static void add();

            inline static RenderAPI::API getApi() { return RenderAPI::getAPI(); }
        };
    }
}
