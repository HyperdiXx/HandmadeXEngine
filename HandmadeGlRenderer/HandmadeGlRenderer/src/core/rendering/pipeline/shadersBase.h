#pragma once

#include "shader.h"


namespace XEngine
{
    namespace Rendering
    {
        class ShaderBases
        {
        public:

            ShaderBases();
            
            void init();
            void addShader(Shader shader);
            static Shader getShaderByName(std::string name);
            inline int getCount() const { return count; }
        private:
            static std::map<std::string, Shader> mShaders;
            std::string basicVert = "baseVertex";
            int count;
        };
    }
}


