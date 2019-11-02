#include "pbrmaterial.h"


XEngine::Rendering::PBRMaterial::PBRMaterial(Shader * pbrShader, Texture2D * diffuse, Texture2D * normal, Texture2D * spec, Texture2D * roug) :
    mShader(pbrShader), mDiffuse(diffuse), mNormal(normal), mSpecular(spec), mRoughness(roug)
{

}

XEngine::Rendering::PBRMaterial::~PBRMaterial()
{
}

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
    mRoughness = tex;
}

void XEngine::Rendering::PBRMaterial::setTextureAO(Texture2D * tex)
{
    mAO = tex;
}

void XEngine::Rendering::PBRMaterial::setShader(Shader *shader)
{
    mShader = shader;
}
