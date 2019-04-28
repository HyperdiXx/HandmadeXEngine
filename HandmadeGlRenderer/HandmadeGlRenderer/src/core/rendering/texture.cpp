
#include "texture.h"



namespace XEngine
{
    uint32 Texture2D::loadtexture2DFromDir(const std::string path, const std::string & dir, bool gamma)
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
    }

    uint32 Texture2D::loadTexture2D(const char* filename)
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
    }

    uint32 Texture2D::loadTextureCubemap(std::vector<std::string> tex)
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
        glTexParameteri(CUBETEXTURE, WRAP_S, CLAMP_EDGE);
        glTexParameteri(CUBETEXTURE, WRAP_T, CLAMP_EDGE);
        glTexParameteri(CUBETEXTURE, WRAP_R, CLAMP_EDGE);

        return textureid;
    }

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
    void Texture2D::bindTexture2D(uint16 n)
    {
        glActiveTexture(GL_TEXTURE0 + n);
        glBindTexture(GL_TEXTURE_2D, dataInRow);
    }

    void Texture2D::bindCubeTexture2D(uint16 n, uint32 tex)
    {
        glActiveTexture(GL_TEXTURE0 + n);
        glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
    }


    void Texture2D::setDepthFunc(int n)
    {
        glDepthFunc(n);
    }

  
}

