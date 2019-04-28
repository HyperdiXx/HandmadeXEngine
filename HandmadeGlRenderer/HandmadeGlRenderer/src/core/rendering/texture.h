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

    class Texture2D
    {
    public:
        Texture2D(const char* path)
        {
            this->path = path;
            loadTexture2D(path);
        }

        Texture2D(std::vector<std::string> text) : mTextures(text)
        {
            
        }

        ~Texture2D()
        {

        }

        uint32 loadTexture2D(const char* filename);
        uint32 loadTextureCubemap(std::vector<std::string> tex);
        uint32 loadTextureHDR(const char* filename);
        uint32 loadtexture2DFromDir(const std::string path, const std::string & dir, bool gamma);

        void bindTexture2D(uint16 n);
        void bindCubeTexture2D(uint16 n, uint32 tex);
        void setDepthFunc(int n);
        //inline const GLuint getID() const { return mID; };

        inline uint32 getTexture() const { return dataInRow; }

    private:
        GLuint mID;
        uint32 dataInRow;
        std::string path;
        std::vector<std::string> mTextures;
    };


}


#endif // !TEXTURE

