#include "context.h"

#include <rendering/render/render.h>

namespace XEngine
{
    namespace Rendering
    {
        DeviceContext * DeviceContext::create(void *win)
        {
            switch (Render::get_api())
            {
            case APIs::RenderAPI::API::OpenGL:
                //return new GLDeviceContext((GLFWwindow*)win);
                break;
            default:
                // LOG:
                break;
            }

            return nullptr;
        }
    }
}