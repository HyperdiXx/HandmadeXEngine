#include "shadersBase.h"



void XEngine::Rendering::ShaderBases::addShader(std::string name, Shader *shader)
{
    count++;
    mShaders.insert(std::pair<std::string, Shader*>(name, shader));
    
}

Shader* XEngine::Rendering::ShaderBases::getShaderByName(std::string name)
{
    return mShaders.at(name);
}
