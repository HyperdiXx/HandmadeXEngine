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
            GLenum format;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureid);
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
            stbi_image_free(data);
        }

        return textureid;
    }


    uint32 loadCubemap(Cubemap *c)
    {
        glGenTextures(1, &c->ID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, c->ID);

        for (GLuint i = 0; i < c->textures.size(); ++i)
        {
            if (c->data)
            {
                c->data = stbi_load((const char*)&c->textures[i], (int*)c->w, (int*)c->h, (int*)c->channels, 0);
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGB, c->w, c->h, 0, GL_RGB, GL_UNSIGNED_BYTE, c->data);
                stbi_image_free(c->data);
            }
            else
            {
                std::cout << "Logger: ERROR_LOADING_TEXTURE_CUBEMAP\n";
            }
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        return (c->ID);       
    }

}

