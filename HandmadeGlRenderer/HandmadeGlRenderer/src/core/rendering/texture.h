#pragma once

#ifndef TEXTURE
#define TEXTURE

#include <stb_image.h>
#include "../types.h"
#include "../rendering/texturetypes.h"
#include "../../xenpch.h"

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

        static uint32 loadTexture2D(const char* filename);
        static uint32 loadTextureCubemap(std::vector<std::string> textures);
        static uint32 loadTextureHDR(const char* filename);
        static uint32 loadtexture2DFromDir(const std::string path, const std::string & dir, bool gamma);

        static void bindTexture2D(uint16 n, uint32 tex1);
        static void bindCubeTexture2D(uint16 n, uint32 tex1);
        static void setDepthFunc(int n);
        //inline const GLuint getID() const { return mID; };

    private:
        //GLuint mID;
    };


}


#endif // !TEXTURE

