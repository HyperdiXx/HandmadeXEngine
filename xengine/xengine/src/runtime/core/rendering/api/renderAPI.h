#pragma once

#ifndef RENDER_API_H
#define RENDER_API_H

#include <runtime/types.h>

#include <math/vec4f.h>

namespace XEngine
{
    namespace Rendering
    {
        class RenderAPI
        {
        public:
            enum class API
            {
                None = 0, 
                OpenGL = 1,
                DX11 = 2, 
                DX12 = 3
            };

        public:
            virtual void init() = 0;
            virtual void clear() = 0;

            virtual void clearColor(real32 r, real32 g, real32 b, real32 a) = 0;
            virtual void setViewport(int32 x, int32 y, int32 width, int32 height) = 0;
                   
            inline static API getAPI() { return API::OpenGL; }
        private:
            static API boundApi;
        };
    }
}

#endif // !RENDER_API_H

