#pragma once

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "texture.h"

namespace XEngine
{
    namespace Rendering
    {
        class Texture2D : public Texture
        {
        public:
            static Texture2D *create(const char* path);
            static Texture2D *create(const char* path, const char* dir);
        };
    }
}
#endif // !TEXTURE2D_H

