#include "gltexture2d.h"

#include <stb_image/stb_image.h>
#include <runtime/core/utility/assert.h>

namespace XEngine
{
    namespace Rendering
    {
        GLTexture2D::GLTexture2D(const char* path) : GLTexture2D(path, nullptr)
        {         
            
        }

        GLTexture2D::GLTexture2D(const char * path, const char* dir)
        {
            Assert(path != nullptr);
            // @Optimize 
            // @Insert own string implementation
            if (dir)
            {
                std::string filename(path);
                std::string dirname(dir);
                filename = dirname + '/' + filename;
                m_path = filename.c_str();
            }
            else
                m_path = path;
            
            int width, height, channels;
            stbi_set_flip_vertically_on_load(true);
            stbi_uc* image = stbi_load(m_path, &width, &height, &channels, 0);
           
            Assert(image != nullptr);
                
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

            glGenTextures(1, &m_id);
            glBindTexture(GL_TEXTURE_2D, m_id);            
         
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          
            glTexImage2D(GL_TEXTURE_2D, 0, m_dataFormat, m_width, m_height, 0, m_dataFormat, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, 0);

            stbi_image_free(image);
        }

        GLTexture2D::~GLTexture2D()
        {
            glDeleteTextures(1, &m_id);
        }

        void GLTexture2D::setup_for_load()
        {

        }

        void GLTexture2D::fillData(void * data, uint32 size)
        {
            uint32 bpp = m_dataFormat == GL_RGBA ? 4 : 3;
            glTexSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
        }

        void GLTexture2D::activate_bind(uint16 index) const
        {
            glActiveTexture(GL_TEXTURE0 + index);
            glBindTexture(GL_TEXTURE_2D, m_id);
        }

        void GLTexture2D::bind() const
        {
            glBindTexture(GL_TEXTURE_2D, m_id);
        }

        void GLTexture2D::unbind() const
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void GLTexture2D::activate(uint16 index) const
        {
            glActiveTexture(GL_TEXTURE0 + index);
        }       
    }
}
