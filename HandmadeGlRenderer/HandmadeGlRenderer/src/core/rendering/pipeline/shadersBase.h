#pragma once

#include "shader.h"


namespace XEngine
{
    namespace Rendering
    {
        class ShaderBases
        {
        public:
            ~ShaderBases();
            void addShader(std::string name, Shader *shader);
            Shader* getShaderByName(std::string name);
            inline int getCount() const { return count; }
        private:
            ShaderBases() {}
            ShaderBases(const ShaderBases&);
            ShaderBases& operator=(ShaderBases&);
        private:
            std::map<std::string, Shader*> mShaders;
            int count;
        public:
            static ShaderBases& getInstance()
            {
                static ShaderBases instance;
                return instance;
            }
        };

       
    }
}


