#include "rendercommand.h"


namespace XEngine
{
    namespace Rendering
    {
        void RenderCommand::init()
        {
            s_api->init();
        }

        void RenderCommand::clear()
        {
            s_api->clear();
        }

        void RenderCommand::clearColor(real32 r, real32 g, real32 b, real32 a)
        {
            s_api->clearColor(r, g, b, a);
        }

        void RenderCommand::setViewport(int32 x, int32 y, int32 width, int32 height)
        {
            s_api->setViewport(x, y, width, height);
        }

        static RenderCommand* s_api = new RenderCommand();
    }
}