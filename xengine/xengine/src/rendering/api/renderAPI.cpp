#include "renderAPI.h"


namespace APIs
{
    RenderAPI::API RenderAPI::boundApi = RenderAPI::API::OpenGL;
    
    UniqPtr<APIs::RenderAPI> RenderAPI::create()
    {
        switch (boundApi)
        {
        case API::OpenGL: 
            return nullptr;
            break;
        default:
            break;
        }
    }
}
