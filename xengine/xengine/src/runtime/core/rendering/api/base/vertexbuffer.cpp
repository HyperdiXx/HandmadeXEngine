#include "vertexbuffer.h"
#include <runtime/core/rendering/render/render.h>
#include <runtime/core/rendering/api/opengl/glvertexbuffer.h>

namespace XEngine
{
    namespace Rendering
    {
        VertexBuffer * VertexBuffer::init(real32 *vertices, uint32 size)
        {
            switch (Render::getApi())
            {
            case RenderAPI::API::None:
                return nullptr;
                break;
            case RenderAPI::API::OpenGL:
                return new GLVertexBuffer(vertices, size);
                break;
            default:
                // LOG: error
                break;
            }
            return nullptr;
        }
    }
}

