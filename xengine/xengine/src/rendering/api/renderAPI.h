#pragma once

#ifndef RENDER_API_H
#define RENDER_API_H

#include <types.h>
#include <math/vec4f.h>

namespace APIs
{
        template<typename T>
        using UniqPtr = std::unique_ptr<T>;
        template<typename T, typename ... Args>
        constexpr UniqPtr<T> create_ptr(Args&& ... args)
        {
            return std::make_unique<T>(std::forward<Args>(args)...);
        }


        class RenderAPI
        {
        public:
            enum class API
            {
                None = 0,
                OpenGL = 1,
                DirectX11 = 2,
                DirectX12 = 3
            };

        public:
            virtual void init() = 0;
            virtual void clear(int flags) = 0;

            virtual void clear_color(real32 r, real32 g, real32 b, real32 a) = 0;
            virtual void set_viewport(int32 x, int32 y, int32 width, int32 height) = 0;
            virtual void draw_indexed(int mode, uint32 count, int type, void *ind) = 0;
            virtual void draw_arrays() = 0;

            inline static API get_api() { return boundApi; }
            
            static UniqPtr<APIs::RenderAPI> create();
        private:
            static API boundApi;
        };
}
#endif // !RENDER_API_H

