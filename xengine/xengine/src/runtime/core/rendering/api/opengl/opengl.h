#pragma once

#ifndef GL_H
#define GL_H

#include <runtime/core/rendering/api/renderAPI.h>

#include <glad/glad.h>

namespace APIs
{
    class OpenGL : public RenderAPI
    {
    public:

        virtual void init() override
        {

        }

        virtual void clear(int flags) override
        {
            glClear(flags);
        }

        virtual void set_viewport(int32 x, int32 y, int32 width, int32 height) override
        {
            glViewport(x, y, width, height);
        }

        virtual void clear_color(real32 r, real32 g, real32 b, real32 a) override
        {
            glClearColor(r, g, b, a);
        }

        virtual void draw_indexed(int mode, uint32 count, int type, void *ind) override
        {
            glDrawElements(mode, count, type, ind);
        }    

        virtual void draw_arrays() override
        {

        }
    };
}
#endif // !GL

