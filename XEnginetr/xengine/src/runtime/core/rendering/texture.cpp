
#include "texture.h"

#include <stb_image.h>

#include "../utility/log.h"

namespace XEngine
{

    bool loadTextureFromFileDir(const char* path, int& width, int &height, TextureType type, int &bpp, void** data)
    {
        //int bpp;

        
        switch (type)
        {
        case XEngine::COLOR:
            *data = stbi_load(path, &width, &height, &bpp, STBI_rgb_alpha);
            break;
        case XEngine::HDR:
            *data = stbi_load(path, &width, &height, &bpp, STBI_rgb_alpha);
            break;
        case XEngine::GREYSCALE:
            *data = stbi_load(path, &width, &height, &bpp, STBI_grey);
            break;
        default:
            break;
        }

        if (!*data)
        {
            Log::error("Failed to load image data!");

            return false;
        }
        
        Log::debug("Loaded texture:" + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(bpp));

        return data;

    }



    /*uint32 Texture2D::loadtexture2DFromDir(const std::string path, const std::string & dir, bool gamma)
    {
        std::string filename = path;
        filename = dir + '/' + filename;

        glGenTextures(1, &dataInRow);

        int width, height, sizechannels;

        unsigned char *data = stbi_load(filename.c_str(), &width, &height, &sizechannels, 0);
        if (data)
        {
            GLenum format;
            if (sizechannels == 1)
                format = GL_RED;
            else if (sizechannels == 3)
                format = GL_RGB;
            else if (sizechannels == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, mID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return mID;
    }*/
    
    Texture::Texture(GLenum target) : target(target)
    {
    }

    void Texture::init()
    {
        glGenTextures(1, &handle);
        created = true;
    }

    void Texture::destroy()
    {
        if (!created)
            return;
        glDeleteTextures(1, &handle);
        created = false;
    }

    void Texture::bind(const uint32 text)
    {
        if (!created)
        {
            Log::error("Cannot bind not inited texture!");
            return;
        }

        glActiveTexture(GL_TEXTURE0 + text);
        glBindTexture(target, handle);
        lastBoundUnit = text;
    }

    void Texture::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::setSampling(TextureSampling minFilter, TextureSampling magFilter, TextureSampling mipFilter)
    {
        if (!isBound())
        {
            bind(lastBoundUnit);
        }

        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, magFilter == NEAREST ? GL_NEAREST : GL_LINEAR);

        if (mipFilter == NONE) 
        {
            glTexParameteri(target, GL_TEXTURE_MAG_FILTER, minFilter == NEAREST ? GL_NEAREST : GL_LINEAR);
        }
        else if (mipFilter == NEAREST) 
        {
            glTexParameteri(target, GL_TEXTURE_MAG_FILTER, minFilter == NEAREST ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_NEAREST);
        }
        else if (mipFilter == LINEAR) 
        {
            glTexParameteri(target, GL_TEXTURE_MAG_FILTER, minFilter == NEAREST ? GL_NEAREST_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_LINEAR);
        }
    }

    void Texture::setMipMapLevel(uint32 level)
    {
        if (!isBound())
        {
            bind(lastBoundUnit);
        }

        glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, level);
    }

    void Texture::generateMipmaps()
    {
        if (!isBound()) { bind(lastBoundUnit); }

        Log::debug("MipMaps generating...");
        glGenerateMipmap(target);
    }

    bool Texture::isBound() const
    {
        return true;
    }


    Texture2D::Texture2D() : Texture(GL_TEXTURE_2D)
    {

    }

    int Texture2D::loadFromFile(const char *path, TextureType type)
    {
        int width, height, channels;
        void *data;
        bool loaded = loadTextureFromFileDir(path, width, height, type, channels, &data);

        if (!loaded) { return false; }

        init();
        
        bind(0);
        
        switch (type) {
        case COLOR:
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
            setData(width, height, GL_SRGB8, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        case GREYSCALE:
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            setData(width, height, GL_R8, GL_RED, GL_UNSIGNED_BYTE, data);
            break;
        case HDR:
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
            setData(width, height, GL_RGBA16F, GL_RGBA, GL_FLOAT, data);
            break;
        }

        generateMipmaps();
        setWrappingMode(REPEAT, REPEAT);
        setSampling(LINEAR, LINEAR, LINEAR);

        setPixel(data);

        //stbi_image_free(data);
        unbind();

        return handle;
    }


    /*uint32 Texture2D::loadTexture2D(const char* filename)
    {
        glGenTextures(1, &dataInRow);

        int width, height, nrChannels;

        unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
        if (data)
        {
            GLenum dataformat, internalF;
            if (nrChannels == 1)
                dataformat = internalF = RED;
            else if (nrChannels == 3)
            {
                internalF = GL_SRGB;
                dataformat = RGB;
            }
            else if (nrChannels == 4)
            {
                internalF = GL_SRGB_ALPHA;
                dataformat = RGBA;
            }

            glBindTexture(TEXTURE2D, dataInRow);
            glTexImage2D(TEXTURE2D, 0, internalF, width, height, 0, dataformat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(TEXTURE2D);

            glTexParameteri(TEXTURE2D, WRAP_S, REPEAT);
            glTexParameteri(TEXTURE2D, WRAP_T, REPEAT);

            glTexParameteri(TEXTURE2D, MIN_FILTER, MIMAP_LINEAR);
            glTexParameteri(TEXTURE2D, MAG_FILTER, LINEAR);


            stbi_image_free(data);
        }
        else
        {
            stbi_image_free(data);
        }

        return dataInRow;
    }*/

    /*uint32 Texture2D::loadTextureCubemap(std::vector<std::string> tex)
    {
        unsigned int textureid;
        glGenTextures(1, &textureid);

        glBindTexture(CUBETEXTURE, textureid);

        int width, height, nrChannels;

        for (uint32 i = 0; i < tex.size(); ++i)
        {
            unsigned char* info = stbi_load(tex[i].c_str(), &width, &height, &nrChannels, 0);
            if (info)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, RGB, width, height, 0, RGB, GL_UNSIGNED_BYTE, info);
                stbi_image_free(info);
            }
            else
            {
                std::cout << "Logger: ERROR_LOADING_TEXTURE_CUBEMAP\n";
            }
        }

        glTexParameteri(CUBETEXTURE, MIN_FILTER, LINEAR);
        glTexParameteri(CUBETEXTURE, MAG_FILTER, LINEAR);
        glTexParameteri(CUBETEXTURE, WRAP_S, CLAMP);
        glTexParameteri(CUBETEXTURE, WRAP_T, CLAMP);
        glTexParameteri(CUBETEXTURE, WRAP_R, CLAMP);

        return textureid;
    }*/


    uint32 Texture2D::loadTextureHDR(const char * filename)
    {
        stbi_set_flip_vertically_on_load(true);
        int width, height, nrComponents;
        float *data = stbi_loadf(filename, &width, &height, &nrComponents, 0);
        unsigned int hdrTexture;
        if (data)
        {
            glGenTextures(1, &hdrTexture);
            glBindTexture(GL_TEXTURE_2D, hdrTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load HDR image." << std::endl;
        }

        return (hdrTexture);

    }

    void Texture2D::setData(uint32 w, uint32 h, GLint intFormat, GLenum format, GLenum type, void * data)
    {
        if (!created) { return; }

        this->width = w;
        this->height = h;

        glTexImage2D(target, 0, intFormat, w, h, 0, format, type, data);
    }

    void Texture2D::setWrappingMode(TextureWrapping swrap, TextureWrapping twrap)
    {
        if (!isBound()) { bind(lastBoundUnit); }

        glTexParameteri(target, GL_TEXTURE_WRAP_S, swrap);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, twrap);
    }

    void Texture2D::setPixel(void * data)
    {
        mdata = data;
    }


    void* Texture2D::getPixel()
    {
        return mdata;
    }

    Cubemap::Cubemap() : Texture(GL_TEXTURE_CUBE_MAP)
    {
    }

    bool Cubemap::loadFromFiles(std::vector<std::string> paths)
    {
        if (paths.size() != 6)
            return false;

        init();
        bind(0);

        for (int i = 0; i < paths.size(); ++i)
        {
            int width, height, channels;
            void* data;
            bool isLoaded = loadTextureFromFileDir(paths[i].c_str(), width, height, COLOR, channels, &data);
            if (!isLoaded)
            {
                destroy();
                return false;
            }

            setFace(face);
            setData(width, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
    
        unbind();
        return true;
    }

    void Cubemap::setData(uint32 resolution, GLint internalFormat, GLenum format, GLenum type, void *data)
    {
        this->resolution = resolution;
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, internalFormat, resolution, resolution, 0, format, type, data);
    }

    void Cubemap::setFace(uint32 face)
    {
        this->face = face;
    }

    void Cubemap::setWrapping(TextureWrapping sWrapping, TextureWrapping tWrapping, TextureWrapping rWrapping)
    {
        if (!isBound()) { bind(lastBoundUnit); }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrapping);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrapping);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, rWrapping);
    }

    void Cubemap::setDepthFunc(uint32 n)
    {
        glDepthFunc(n);
    }

    Texture3D::Texture3D() : Texture(GL_TEXTURE_3D)
    {
    }

    bool Texture3D::loadFromFile(const char * path, TextureType type)
    {
        int width, height, channels;
        void *data;
        bool loaded = loadTextureFromFileDir(path, width, height, type, channels, &data);

        if (!loaded) { return false; }

        init();
        bind(GL_TEXTURE0);

        switch (type) 
        {
        case COLOR:
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
            setData(height, height, height, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        case GREYSCALE:
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            setData(height, height, height, GL_R8, GL_RED, GL_UNSIGNED_BYTE, data);
            break;
        case HDR:
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
            setData(height, height, height, GL_RGBA16F, GL_RGBA, GL_FLOAT, data);
            break;
        }

        unbind();

        return true;
    }

    void Texture3D::setData(uint32 width, uint32 height, uint32 depth, GLint internalFormat, GLenum format, GLenum type, void* data)
    {
        this->width = width;
        this->height = height;
        this->depth = depth;

        glTexImage3D(target, 0, internalFormat, width, height, depth, 0, format, type, data);
    }

    void Texture3D::setWrapping(TextureWrapping sWrapping, TextureWrapping tWrapping, TextureWrapping rWrapping)
    {
        if (!isBound()) { bind(lastBoundUnit); }

        glTexParameteri(target, GL_TEXTURE_WRAP_S, sWrapping);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, tWrapping);
        glTexParameteri(target, GL_TEXTURE_WRAP_R, rWrapping);
    }

}

