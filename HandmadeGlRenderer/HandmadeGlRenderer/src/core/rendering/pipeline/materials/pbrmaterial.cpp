#include "pbrmaterial.h"


void XEngine::Rendering::PBRMaterial::setTextureDiffuse(Texture2D * tex)
{
    mDiffuse = tex;
}

void XEngine::Rendering::PBRMaterial::setTextureNormal(Texture2D * tex)
{
    mNormal = tex;
}

void XEngine::Rendering::PBRMaterial::setTextureSpecular(Texture2D * tex)
{
    mSpecular = tex;
}

void XEngine::Rendering::PBRMaterial::setTextureRough(Texture2D * tex)
{
    mRoughnes = tex;
}

void XEngine::Rendering::PBRMaterial::setTextureAO(Texture2D * tex)
{
    mAO = tex;
}

void XEngine::Rendering::PBRMaterial::setShader(Shader *shader)
{
    mShader = shader;
}
