#pragma once

#ifndef SHADER
#define SHADER

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/core/types.h"
#include "shadertype.h"

#include <string>

class Shader
{
public:
    Shader(const GLchar* vs1, const GLchar* fs1)
    {
        this->vs = vs1;
        this->fs = fs1;
    }
    ~Shader()
    {
        vs = nullptr;
        fs = nullptr;
    }

    void Win32SetShaderName();

    void Win32SetupShaders();
    void Win32UseShader();

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

private:
    uint32 ID;

    const GLchar* vs;
    const GLchar* fs;
};

#endif // !SHADER