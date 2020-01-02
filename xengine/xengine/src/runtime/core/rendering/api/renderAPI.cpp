#include "renderAPI.h"

#include <runtime/core/rendering/api/opengl/opengl.h> 

namespace APIs
{


    RenderAPI::API RenderAPI::boundApi = RenderAPI::API::OpenGL;
    
    UniqPtr<APIs::RenderAPI> RenderAPI::create()
    {
        switch (boundApi)
        {
        case API::OpenGL: 
            return create_ptr<OpenGL>();
            break;
        default:
            break;
        }
    }
}
