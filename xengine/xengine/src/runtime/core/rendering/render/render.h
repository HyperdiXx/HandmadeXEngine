#pragma once

#ifndef RENDER_H
#define RENDER_H

#include <runtime/core/rendering/api/renderAPI.h>
#include <runtime/core/rendering/commands/rendercommand.h>

#include <xenpch.h>

namespace XEngine
{
    class OrthoCamera;
    class RenderCommandExecutor;

    namespace Assets
    {
        class Model;
    }

    namespace Rendering
    {
        class Render
        {
        public:
            virtual ~Render() {};

            virtual void clear(int flags) = 0;
            virtual void clear_color(real32 r, real32 g, real32 b, real32 a) = 0;
            virtual void set_viewport(int32 x, int32 y, int32 width, int32 height) = 0;
            
            virtual void draw_model(Assets::Model *model) = 0;
            virtual void draw_quad() = 0;

            virtual void create_texture2D() = 0;
            virtual void create_shader() = 0;
            virtual void create_framebuffer() = 0;
            
            void start_execution();
            void end_execution();

            void add(RenderCommand *command);

            static APIs::RenderAPI::API get_api() { return APIs::RenderAPI::get_api(); }

            static Render *create();

        private:
            std::vector<RenderCommand*> m_commands;
            RenderCommandExecutor *m_command_executor = nullptr;;
        };
    }
}
#endif // !RENDER_H

