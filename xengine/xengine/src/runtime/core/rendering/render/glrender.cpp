#include "glrender.h"

#include <runtime/core/rendering/commands/model_command.h>
#include <runtime/core/rendering/commands/quad_rendercommand.h>

namespace XEngine
{
    namespace Rendering
    {
        void GLRender::clear(int flags)
        {
            RenderCommand::clear(flags);
        }

        void GLRender::clear_color(real32 r, real32 g, real32 b, real32 a)
        {
            RenderCommand::clear_color(r, g, b, a);
        }

        void GLRender::set_viewport(int32 x, int32 y, int32 width, int32 height)
        {
            RenderCommand::set_viewport(x, y, width, height);
        }

        void GLRender::draw_model(Assets::Model *model)
        {
            add(new ModelRenderCommand("TestModel", RenderCommandType::MODEL));
        }

        void GLRender::draw_quad()
        {
            add(new QuadRenderCommand("TestQuad", RenderCommandType::QUAD));
        }
    }
}
