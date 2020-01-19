#pragma once


#ifndef TEXTURE_H
#define TEXTURE_H

#include <runtime/types.h>

namespace XEngine
{
    namespace Rendering
    {
        class Texture
        {
        public:
            virtual uint32 getWidth() const = 0;
            virtual uint32 getHeight() const = 0;

            virtual void fillData(void* data, uint32 size) = 0;
            virtual void activate_bind(uint16 index) const = 0;   
            virtual void bind() const = 0;
            virtual void unbind() const = 0;
            virtual void activate(uint16 index) const = 0;
        };
    }
}

#endif // !TEXTURE_H
