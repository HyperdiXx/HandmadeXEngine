#pragma once

#ifndef GL_RENDER_API_H
#define GL_RENDER_API_H

#include <runtime/core/rendering/api/renderAPI.h>

namespace XEngine
{
    namespace Rendering
    {
        class OpenGLRenderAPI : public RenderAPI
        {
        public:
            virtual void init() override;
            virtual void setViewport(int32 x, int32 y, int32 width, int32 height) override;

            virtual void clear() override;
            virtual void clearColor(real32 r, real32 g, real32 b, real32 a) override;
        };
    }
}

#endif // !GL_RENDER_API

