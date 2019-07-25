#include "shadersBase.h"

namespace XEngine
{
    namespace Rendering
    {
        void ShaderBases::addShader(std::string name, Shader *shader)
        {
            count++;
            mShaders.insert(std::pair<std::string, Shader*>(name, shader));
        }

        Shader* ShaderBases::getShaderByName(std::string name)
        {
            return mShaders.at(name);
        }

    }
}
