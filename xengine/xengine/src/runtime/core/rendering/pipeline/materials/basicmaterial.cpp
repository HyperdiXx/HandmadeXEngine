#include "basicmaterial.h"

#include "basicmaterial.h"

XEngine::Rendering::BasicMaterial::BasicMaterial(Shader *shd) : mShader(shd)
{

}

XEngine::Rendering::BasicMaterial::BasicMaterial(Shader *shd, Texture2D *tex) : mShader(shd), mTexture(tex)
{
}

void XEngine::Rendering::BasicMaterial::set_texture2D(Texture2D *tex)
{
    mTexture = tex;
}

void XEngine::Rendering::BasicMaterial::set_shader(Shader *shader)
{
    mShader = shader;
}
