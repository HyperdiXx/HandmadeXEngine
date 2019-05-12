#pragma once

#ifndef SHADER
#define SHADER


#include "src/xenpch.h"
#include "src/core/types.h"
#include "shadertype.h"


class Shader
{
public:
    Shader() {};
    Shader(const GLchar* vs1, const GLchar* fs1)
    {
        this->vs = vs1;
        this->fs = fs1;
        setupShaderFile();
    }
    ~Shader()
    {
        vs = nullptr;
        fs = nullptr;
        glDeleteProgram(ID);
    }

    void setupShaderFile();
    void enableShader();
    void disableShader();
    void linkPrograms();
    Shader* addShader(Shader &shader);

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

    std::list<unsigned int> shaders;
    std::string name;

    bool linked, isCompute;
};

#endif // !SHADER