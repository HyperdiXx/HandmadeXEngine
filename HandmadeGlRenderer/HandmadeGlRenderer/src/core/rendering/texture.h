#pragma once

#ifndef TEXTURE
#define TEXTURE

#include "../types.h"
#include <vector>

namespace XEngine
{
   
    struct Cubemap
    {
        uint32 ID;
        uint32 w, h, channels;
        unsigned char *data;

        std::vector<std::string> textures;
    };

    class Texture2d
    {
    public:
        Texture2d(const char* path)
        {

        }

        ~Texture2d()
        {

        }

        void loadTexture2d();
        void loadTextureCubemap();
        static void bindTexture2D(uint16 n, uint32 tex1);
        static void bindCubeTexture2D(uint16 n, uint32 tex1);
        static void setDepthFunc(int n);
    };


}


#endif // !TEXTURE

