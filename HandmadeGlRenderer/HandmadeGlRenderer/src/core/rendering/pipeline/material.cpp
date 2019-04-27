#include "material.h"

namespace XEngine
{
    namespace Rendering
    {
        Material::Material(Shader * shader) : mShader(shader)
        {

        }

        Material::Material(Shader * shader, Texture2D * mtext)
        {
            mShader = shader;
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