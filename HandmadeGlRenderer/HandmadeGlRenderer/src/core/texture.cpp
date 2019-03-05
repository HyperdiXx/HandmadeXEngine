#include "../xenpch.h"
#include "texture.h"

namespace XEngine
{
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
                
            glBindTexture(TEXTURE2D, textureid);
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

        return textureid;
    }

    void bindTexture2D(uint16 n, uint32 tex1)
    {
        glActiveTexture(GL_TEXTURE0 + n);
        glBindTexture(GL_TEXTURE_2D, tex1);
    }

    void bindCubeTexture2D(uint16 n, uint32 tex1)
    {
        glActiveTexture(GL_TEXTURE0 + n);
        glBindTexture(GL_TEXTURE_CUBE_MAP, tex1);
    }


    void setDepthFunc(int n)
    {
        glDepthFunc(n);
    }

    uint32 loadCubemap(std::vector<std::string> textures)
    {
        unsigned int textureid;
        glGenTextures(1, &textureid);

        glBindTexture(CUBETEXTURE, textureid);

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

        glTexParameteri(CUBETEXTURE, MIN_FILTER, LINEAR);
        glTexParameteri(CUBETEXTURE, MAG_FILTER, LINEAR);
        glTexParameteri(CUBETEXTURE, WRAP_S, CLAMP_EDGE);
        glTexParameteri(CUBETEXTURE, WRAP_T, CLAMP_EDGE);
        glTexParameteri(CUBETEXTURE, WRAP_R, CLAMP_EDGE);

        return textureid;       
    }

}

