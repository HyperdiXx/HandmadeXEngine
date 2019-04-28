#include "material.h"

namespace XEngine
{
    namespace Rendering
    {
        
        Material::Material(Shader* shd) : mShader(shd)
        {
          
        }

        Material::Material(Shader* shd, Texture2D* tex) :
            mShader(shd), mTexture(tex)
        {
            
        }

        Material::Material(const Material & mat)
        {
        }

        void Material::setTexture(uint32 data)
        {

        }

        void Material::setShader(Shader shader)
        {

        }
    }
}