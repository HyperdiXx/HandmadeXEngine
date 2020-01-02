#pragma once

#ifndef GL_RENDER_H
#define GL_RENDER_H

#include "render.h"

namespace XEngine
{
    namespace Rendering
    {
        class GLRender : public Render
        {
        public:
            
            virtual void clear(int flags) override;
            virtual void clear_color(real32 r, real32 g, real32 b, real32 a) override;
            virtual void set_viewport(int32 x, int32 y, int32 width, int32 height) override;

            virtual void draw_model(Assets::Model *model) override;
            virtual void draw_quad() override;

            virtual void create_texture2D() override {};
            virtual void create_shader() override {};
            virtual void create_framebuffer() override {};
        private:

        };
    }
}
#endif // GL_RENDER_H

