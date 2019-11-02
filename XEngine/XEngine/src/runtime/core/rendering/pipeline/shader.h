#pragma once

#ifndef SHADER
#define SHADER


#include <xenpch.h>
#include <runtime/types.h>
#include "shadertype.h"


namespace XEngine
{
    class Shader
    {
    public:
        Shader() {};
        Shader(const char* vs1, const char* fs1)
        {
            this->vs = vs1;
            this->fs = fs1;
            convertShaderCode();
        }
        ~Shader()
        {
            vs = nullptr;
            fs = nullptr;
            glDeleteProgram(ID);
        }

        void convertShaderCode();
        void setupBasicShader();
        void enableShader();
        void disableShader();
        void linkPrograms();
        Shader* addShaderCompute(const GLchar* cs);

        const GLchar* Win32GetFsName();
        const GLchar* Win32GetVsName();

        void setBool(const std::string &name, bool value);
        void setInt(const std::string &name, int value);
        void setFloat(const std::string& name, float value);
        void setVec2(const std::string &name, const glm::vec2 &value);
        void setVec2(const std::string &name, float x, float y);
        void setVec3(const std::string &name, const glm::vec3 &value);
        void setVec3(const std::string &name, float x, float y, float z);
        void setVec4(const std::string &name, const glm::vec4 &value);
        void setVec4(const std::string &name, float x, float y, float z, float w);
        void setMat2(const std::string &name, const glm::mat2 &mat);
        void setMat3(const std::string &name, const glm::mat3 &mat);
        void setMat4(const std::string &name, const glm::mat4 &mat);

        uint32 getID() { return ID; };
        std::string getName() { return name; }
    private:
        uint32 ID;

        const GLchar* vs;
        const GLchar* fs;

        const char* vsFileCode;
        const char* fsFileCode;

        std::list<unsigned int> shaders;
        std::string name;

        bool linked, isCompute;
    };

}
#endif // !SHADER