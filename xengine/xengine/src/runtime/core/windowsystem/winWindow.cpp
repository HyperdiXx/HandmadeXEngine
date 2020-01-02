#include "winWindow.h"

#include <runtime/core/rendering/render/render.h>

namespace XEngine
{
    Window * Window::create(const char * t, const uint32 w, const uint32 h)
    {
        using namespace Rendering;

        switch (Render::get_api())
        {
        case APIs::RenderAPI::API::OpenGL:
            break;
        default:
            break;
        }

        return nullptr;
    }
}
