#pragma once



#include "../rendering/texturetypes.h"
#include "../types.h"
#include "../../xenpch.h"

namespace XEngine
{
  
   
    class Texture
    {
    public:
        Texture(GLenum target);
        static const unsigned int MAX_TEXTURE_UNITS = 16;

        void init();
        void destroy();
        void bind(const uint32 text);
        void unbind();

        void setSampling(TextureSampling minFilter, TextureSampling magFilter, TextureSampling mipFilter);
        void setMipMapLevel(uint32 level);
        void generateMipmaps();

        GLuint getHandle() { return handle; }
        
        bool isCreated() const { return created; }
       
        bool isBound() const;

    protected:
        bool created = false;
        GLuint handle;
        GLenum target;
        mutable uint32 lastBoundUnit = 0;
    };


    class Texture2D : public Texture
    {
    public:
        Texture2D();
               
        int loadFromFile(const char* path, TextureType type);
        //int load2dTexture(const char* filename, TextureType type);
       

        //uint32 loadTexture2D(const char* filename);
        //uint32 loadTextureCubemap(std::vector<std::string> tex);
        uint32 loadTextureHDR(const char* filename);
        //uint32 loadtexture2DFromDir(const std::string path, const std::string & dir, bool gamma);
        
        void setData(uint32 w, uint32 h, GLint intFormat, GLenum format, GLenum type, void* data);
        void setWrappingMode(TextureWrapping swrap, TextureWrapping twrap);

        void setPixel(void *data);
        void* getPixel();

        uint32 getWidth() const { return width; }

        uint32 getHeight() const {  return height; }

    private:
        uint32 width;
        uint32 height;
        void *mdata;
    };

    class Texture3D : public Texture
    {
    public:
        Texture3D();

        bool loadFromFile(const char* path, TextureType type);

        void setData(uint32 width, uint32 height, uint32 depth, GLint internalFormat, GLenum format, GLenum type, void* data);
        void setWrapping(TextureWrapping sWrapping, TextureWrapping tWrapping, TextureWrapping rWrapping);

        uint32 getWidth() const { return width; }
        uint32 getHeight() const { return height; }
        uint32 getDepth() const { return depth; }
    private:
        uint32 width;
        uint32 height;
        uint32 depth;
    };

    class Cubemap : public Texture
    {
    public:
        Cubemap();

        bool loadFromFiles(std::vector<std::string> paths);

        void setData(uint32 resolution, GLint internalFormat, GLenum format, GLenum type, void* data);
        void setFace(uint32 face);
        void setWrapping(TextureWrapping sWrapping, TextureWrapping tWrapping, TextureWrapping rWrapping);

        void setDepthFunc(uint32 n);

        uint32 getResolution() const { return resolution; }
    private:
        uint32 resolution;
        uint32 face;
    };
}

