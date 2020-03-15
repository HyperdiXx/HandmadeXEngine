#pragma once

#include <rendering/api/renderAPI.h>
#include <rendering/commands/abstract_render_command.h>
#include <xenpch.h>

namespace XEngine
{
    namespace Rendering
    {
        class RenderCommand
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

            inline static void draw_arrays()
            {
                s_api->draw_arrays();
            }

            inline static void draw_indexed(int mode, uint32 count, int type, void *indices)
            {
                s_api->draw_indexed(mode, count, type, indices);
            }

            virtual void execute() = 0;

        private:
            static std::unique_ptr<APIs::RenderAPI> s_api;        
        };
    }
}
