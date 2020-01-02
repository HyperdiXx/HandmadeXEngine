#include "shader.h"

#include <runtime/core/rendering/render/render.h>
#include <runtime/core/rendering/api/opengl/glshader.h>

namespace XEngine
{
    namespace Rendering
    {

        Shader * Shader::create(const std::string & filepath)
        {
            return nullptr;
        }

        Shader * Shader::create(const std::string & vertexSrc, const std::string & fragmentSrc)
        {
            switch (Render::get_api())
            {
            case APIs::RenderAPI::API::OpenGL: return new GLShader(vertexSrc, fragmentSrc);
                    break;
                default:
                    break;
            }
            return nullptr;
        }
    }
}
