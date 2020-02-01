#include "rendercommand.h"


namespace XEngine
{
    namespace Rendering
    {
        std::unique_ptr<APIs::RenderAPI> RenderCommand::s_api = APIs::RenderAPI::create();
    }
}
