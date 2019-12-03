#include "texture2d.h"

#include <runtime/core/rendering/render/render.h>
#include <runtime/core/rendering/api/opengl/gltexture2d.h>

namespace XEngine
{
    namespace Rendering
    {
        Texture2D * Texture2D::create(const char * path)
        {
            switch (Render::getApi())
            {
                case RenderAPI::API::OpenGL: return new GLTexture2D(path);
                    break;
            }

            return nullptr;
        }
    }
}