#include "shadersBase.h"

XEngine::Rendering::ShaderBases::ShaderBases()
{
    init();
}

void XEngine::Rendering::ShaderBases::init()
{
    count = 0;



}

void XEngine::Rendering::ShaderBases::addShader(Shader shader)
{
    count++;
    std::string name;
    mShaders.insert(std::pair<std::string, Shader>(name, shader));
    
}

Shader XEngine::Rendering::ShaderBases::getShaderByName(std::string name)
{
    return  mShaders.at(name);
}
