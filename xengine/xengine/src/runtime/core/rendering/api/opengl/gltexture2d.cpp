#include "gltexture2d.h"

#include <stb_image/stb_image.h>


namespace XEngine
{
    namespace Rendering
    {
        GLTexture2D::GLTexture2D(const char * path)
        {
            m_path = path;
            int width, height, channels;
            stbi_set_flip_vertically_on_load(true);
            stbi_uc* image = stbi_load(path, &width, &height, &channels, 0);
           
            // Assert
                
            m_width = width;
            m_height = height;

            GLenum internalFormat = 0, dataFormat = 0;
            if (channels == 4)
            {
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
            }
            else if (channels == 3)
            {
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
            }

            m_internalFormat = internalFormat;
            m_dataFormat = dataFormat;

            glGenTextures(GL_TEXTURE_2D, &m_id);
            glBindTexture(GL_TEXTURE_2D, m_id);            
         
            glTexParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTexImage2D(GL_TEXTURE_2D, 0, m_dataFormat, m_width, m_height, 0, m_dataFormat, GL_UNSIGNED_BYTE, image);
            //glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(image);
        }

        GLTexture2D::~GLTexture2D()
        {
            glDeleteTextures(1, &m_id);
        }

        void GLTexture2D::fillData(void * data, uint32 size)
        {
            uint32 bpp = m_dataFormat == GL_RGBA ? 4 : 3;
            glTexSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
            //glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
        }

        void GLTexture2D::bind() const
        {
            //glActiveTexture(GL_TEXTURE0 + m_id);
            glBindTexture(GL_TEXTURE_2D, m_id);
        }
    }
}
