#pragma once

#ifndef GL_SHADER_H
#define GL_SHADER_H


#include <xenpch.h>
#include <types.h>

#include <rendering/api/base/shader.h>

#include <math/mat4.h>
#include <math/mat3.h>


namespace XEngine
{
   namespace Rendering
   {
       class GLShader : public Shader
       {
       public:
           GLShader() {};
           GLShader(const std::string &vs, const std::string &fs)
           {
               this->vs = vs.c_str();
               this->fs = fs.c_str();
               convertShaderCode();
               setupBasicShader();
           }
           virtual ~GLShader()
           {
               vs = nullptr;
               fs = nullptr;
               glDeleteProgram(ID);
           }

           virtual void bind() const override;
           virtual void unbind() const override;

           void convertShaderCode();
           
           void setupBasicShader();

           void linkPrograms();
           GLShader* addShaderCompute(const GLchar* cs);

           const GLchar* win32GetFsName();
           const GLchar* win32GetVsName();

           virtual void setBool(const std::string &name, bool value);
           virtual void setInt(const std::string &namee, int value);
           virtual void setFloat(const std::string& name, float value);
           virtual void setVec2(const std::string &name, const glm::vec2 &value);
           virtual void setVec2(const std::string &name, float x, float y);
           virtual void setVec3(const std::string &name, const glm::vec3 &value);
           virtual void setVec3(const std::string &name, float x, float y, float z);
           virtual void setVec4(const std::string &name, const glm::vec4 &value);
           virtual void setVec4(const std::string &name, float x, float y, float z, float w);
           virtual void setMat2(const std::string &name, const glm::mat2 &mat);
           virtual void setMat3(const std::string &name, const glm::mat3 &mat);
           virtual void setMat4(const std::string &name, const glm::mat4 &mat);

           uint32 getID() { return ID; };
           virtual const std::string& getName() const;
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
}
#endif // !SHADER