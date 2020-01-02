#include "vertexarray.h"
#include <runtime/core/rendering/render/render.h>
#include <runtime/core/rendering/api/opengl/glvertexarray.h>

namespace XEngine
{
    namespace Rendering
    {
        VertexArray *VertexArray::create()
        {
            switch (Render::get_api())
            {
            case APIs::RenderAPI::API::None:
                return nullptr;
                break;
            case APIs::RenderAPI::API::OpenGL:
                return new GLVertexArray();
                break;
            default:
                // LOG: error
                break;
            }
            return nullptr;
        }
    }
}
