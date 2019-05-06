#pragma once

#ifndef TEXTURELOADH
#define TEXTURELOADH

#include <stb_image.h>

#include "../../xenpch.h"
#include "../rendering/texturetypes.h"
#include "../types.h"

namespace XEngine
{
    namespace Utils
    {
        uint32 loadCubemap(std::vector<std::string> textures)
        {
            unsigned int textureid;
            glGenTextures(1, &textureid);

            glBindTexture(GL_TEXTURE_CUBE_MAP, textureid);

            int width, height, nrChannels;

            for (uint32 i = 0; i < textures.size(); ++i)
            {
                unsigned char* info = stbi_load(textures[i].c_str(), &width, &height, &nrChannels, 0);
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

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, CLAMP);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, CLAMP);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, CLAMP);

            return textureid;
        }

        int loadTextureHDR(const char* filename)
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


        int loadTexture(const char* filename)
        {
            unsigned int textureid;
            glGenTextures(1, &textureid);

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

                glBindTexture(GL_TEXTURE_2D, textureid);
                glTexImage2D(GL_TEXTURE_2D, 0, internalF, width, height, 0, dataformat, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, REPEAT);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, LINEAR);


                stbi_image_free(data);
            }
            else
            {
                stbi_image_free(data);
            }

            return textureid;
        }

        uint32 loadtexture2DFromDir(const std::string path, const std::string & dir, bool gamma)
        {
            std::string filename = path;
            filename = dir + '/' + filename;

            uint32 textureID;
            glGenTextures(1, &textureID);

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

                glBindTexture(GL_TEXTURE_2D, textureID);
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

            return textureID;
        }

    }

}


#endif // !TEXTURELOADH

