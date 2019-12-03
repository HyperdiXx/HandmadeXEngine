
#include "glshader.h"

#include <runtime/core/systems/filefunc.h>

namespace XEngine
{
    namespace Rendering
    {
        void GLShader::convertShaderCode()
        {
            std::string fileVs = FileUtils::readFileEngine(vs);
            std::string fileFs = FileUtils::readFileEngine(fs);
            vsFileCode = fileVs.c_str();
            fsFileCode = fileFs.c_str();
        }

        void GLShader::setupBasicShader()
        {
            unsigned int vertex, fragment;

            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vsFileCode, NULL);
            glCompileShader(vertex);

            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fsFileCode, NULL);
            glCompileShader(fragment);

            GLint status;
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);

            if (status != GL_TRUE)
            {
                GLint length;
                glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);

                GLchar* buffer = new GLchar[length];
                GLint buflength;
                glGetShaderInfoLog(vertex, length, &buflength, buffer);

                printf("%s\n", buffer);

                delete[] buffer;
            }

            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);
            glValidateProgram(ID);

            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }

        void GLShader::bind() const
        {
            glUseProgram(ID);
        }

        void GLShader::unbind() const 
        {
            glUseProgram(0);
        }

        void GLShader::linkPrograms()
        {
            glLinkProgram(ID);

            if (true) //TODO: implement error checking 
            {
                linked = true;
                while (!shaders.empty())
                {
                    glDeleteShader(shaders.back());
                    shaders.pop_back();
                }
            }
            else
            {

            }
        }

        GLShader* GLShader::addShaderCompute(const GLchar* cs)
        {
            if (!isCompute)
            {
                //glAttachShader(ID, shader.getID());
                //if (shader.getName() == "compute")
                 //   isCompute = true;
                //this->shaders.push_back(shader.getID());
            }
            else
            {

            }

            return this;
        }

        const GLchar * GLShader::win32GetFsName()
        {
            return fs;
        }

        const GLchar * GLShader::win32GetVsName()
        {
            return vs;
        }

        void GLShader::setBool(const std::string& name, bool value)
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }

        void GLShader::setInt(const std::string& name, int value)
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }

        void GLShader::setFloat(const std::string& name, float value)
        {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }

        void GLShader::setVec2(const std::string& name, const glm::vec2 & value)
        {
            glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }

        void GLShader::setVec2(const std::string& name, float x, float y)
        {
            glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
        }

        void GLShader::setVec3(const std::string& name, const glm::vec3 & value)
        {
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }

        void GLShader::setVec3(const std::string& name, float x, float y, float z)
        {
            glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
        }

        void GLShader::setVec4(const std::string& name, const glm::vec4 & value)
        {
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }

        void GLShader::setVec4(const std::string& name, float x, float y, float z, float w)
        {
            glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
        }

        void GLShader::setMat2(const std::string& name, const glm::mat2 & mat)
        {
            glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void GLShader::setMat3(const std::string& name, const glm::mat3 & mat)
        {
            glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void GLShader::setMat4(const std::string& name, const glm::mat4 & mat)
        {
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        const std::string & GLShader::getName() const
        {
            return name;
        }
    }
}
