#pragma once

#ifndef SHADER
#define SHADER

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../types.h"
#include "shadertype.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

struct Shader
{
    uint32 ID;

    const GLchar* vs;
    const GLchar* fs;

}; 

void Win32SetShaderName(Shader *shader);

void Win32SetupShaders(Shader *shader, const char* vs, const char* fs);
void Win32UseShader(Shader *shader);

const GLchar* Win32GetFsName(Shader *shader);
const GLchar* Win32GetVsName(Shader *shader);

void setBool(Shader *shader, const std::string &name, bool value);
void setInt(Shader *shader, const std::string &name, int value);
void setFloat(Shader *shader, const std::string name, float value);
void setVec2(Shader *shader, const std::string &name, const glm::vec2 &value);
void setVec2(Shader *shader, const std::string &name, float x, float y);
void setVec3(Shader *shader, const std::string &name, const glm::vec3 &value);
void setVec3(Shader *shader, const std::string &name, float x, float y, float z);
void setVec4(Shader *shader, const std::string &name, const glm::vec4 &value);
void setVec4(Shader *shader, const std::string &name, float x, float y, float z, float w);
void setMat2(Shader *shader, const std::string &name, const glm::mat2 &mat);
void setMat3(Shader *shader, const std::string &name, const glm::mat3 &mat);
void setMat4(Shader *shader, const std::string &name, const glm::mat4 &mat);
#endif // !SHADER