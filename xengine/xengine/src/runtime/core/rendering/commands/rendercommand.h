#pragma once

#include <runtime/core/rendering/api/renderAPI.h>
#include <runtime/core/rendering/api/opengl/opengl.h>
#include <runtime/core/rendering/commands/abstract_render_command.h>
#include <xenpch.h>

namespace XEngine
{
    namespace Rendering
    {
        class RenderCommand : public AbstractRenderCommand
        {
        public:
            
            inline static void init()
            {
                s_api->init();
            }

            inline static void clear(int flags)
            {
                s_api->clear(flags);
            }

            inline static void clear_color(real32 r, real32 g, real32 b, real32 a)
            {
                s_api->clear_color(r, g, b, a);
            }

            inline static void set_viewport(int32 x, int32 y, int32 width, int32 height)
            {
                s_api->set_viewport(x, y, width, height);
            }
        private:
            static std::unique_ptr<APIs::RenderAPI> s_api;
        };
    }
}
