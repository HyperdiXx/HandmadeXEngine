#include "winWindow.h"

#include <runtime/core/rendering/render/render.h>

namespace XEngine
{
    Window * Window::create(const char * t, const uint32 w, const uint32 h)
    {
        using namespace Rendering;

        switch (Render::getApi())
        {
        case RenderAPI::API::OpenGL:
            
        default:
            break;
        }

        return nullptr;
    }
}
