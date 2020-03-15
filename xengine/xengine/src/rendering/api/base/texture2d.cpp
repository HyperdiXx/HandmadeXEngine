#include "texture2d.h"

#include <rendering/render/render.h>

namespace XEngine
{
    namespace Rendering
    {
        Texture2D * Texture2D::create(const char * path)
        {
            switch (Render::get_api())
            {
            case APIs::RenderAPI::API::OpenGL: 
                //return new GLTexture2D(path);
                    break;
                default:
                    // Log : "Unsoppurted format!!!"
                    break;
            }

            return nullptr;
        }

        Texture2D * Texture2D::create(const char * path, const char* dir)
        {
            switch (Render::get_api())
            {
            //case APIs::RenderAPI::API::OpenGL: return new GLTexture2D(path, dir);
                break;
            default:
                // Log : "Unsoppurted format!!!"
                break;
            }

            return nullptr;
        }
    }
}