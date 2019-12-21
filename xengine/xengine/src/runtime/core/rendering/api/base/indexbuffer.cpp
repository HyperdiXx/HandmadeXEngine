#include "indexbuffer.h"

#include <runtime/core/rendering/render/render.h>
#include <runtime/core/rendering/api/opengl/glindexbuffer.h>

namespace XEngine
{
    namespace Rendering
    {
        IndexBuffer * IndexBuffer::create(uint32* indices, uint32 size)
        {
            switch (Render::getApi())
            {
            case RenderAPI::API::OpenGL:
                return new GLIndexBuffer(indices, size);
                break;
            default:
                // LOG:
                break;
            }

            return nullptr;
        }
    }
}

