#include "indexbuffer.h"

#include <runtime/core/rendering/render/render.h>
#include <runtime/core/rendering/api/opengl/glindexbuffer.h>

namespace XEngine
{
    namespace Rendering
    {
        IndexBuffer * IndexBuffer::create(uint32* indices, uint32 size)
        {
            switch (Render::get_api())
            {
            case APIs::RenderAPI::API::OpenGL:
                return new GLIndexBuffer(indices, size);
                break;
            default:
                // LOG:
                break;
            }

            return nullptr;
        }

        IndexBuffer * IndexBuffer::create(std::vector<uint32> indices, uint32 size)
        {
            switch (Render::get_api())
            {
            case APIs::RenderAPI::API::OpenGL:
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

