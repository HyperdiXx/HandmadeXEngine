#include "vertexbuffer.h"
#include <rendering/render/render.h>
#include <rendering/api/opengl/glvertexbuffer.h>

namespace XEngine
{
    namespace Rendering
    {
        VertexBuffer *VertexBuffer::create(real32 *vertices, uint32 size)
        {
            switch (Render::get_api())
            {
            case APIs::RenderAPI::API::None:
                return nullptr;
                break;
            case APIs::RenderAPI::API::OpenGL:
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

