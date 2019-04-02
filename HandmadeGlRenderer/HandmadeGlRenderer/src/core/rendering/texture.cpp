#include "../../xenpch.h"
#include "texture.h"

namespace XEngine
{
    void Texture2d::loadTexture2d()
    {

    }
    void Texture2d::loadTextureCubemap()
    {

    }
    void Texture2d::bindTexture2D(uint16 n, uint32 tex1)
    {
        glActiveTexture(GL_TEXTURE0 + n);
        glBindTexture(GL_TEXTURE_2D, tex1);
    }

    void Texture2d::bindCubeTexture2D(uint16 n, uint32 tex1)
    {
        glActiveTexture(GL_TEXTURE0 + n);
        glBindTexture(GL_TEXTURE_CUBE_MAP, tex1);
    }


    void Texture2d::setDepthFunc(int n)
    {
        glDepthFunc(n);
    }

  
}

