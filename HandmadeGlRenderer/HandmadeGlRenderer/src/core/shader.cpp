#include "shader.h"


void Win32SetShaderName(Shader *shader)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(shader->vs);
        fShaderFile.open(shader->fs);
        std::stringstream vShaderStream, fShaderStream;
    
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        vShaderFile.close();
        fShaderFile.close();
        
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    shader->ID = glCreateProgram();
    glAttachShader(shader->ID, vertex);
    glAttachShader(shader->ID, fragment);
    glLinkProgram(shader->ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Win32SetupShaders(Shader* shader, const char* vs, const char* fs)
{
    UINT32 vertex, fragment;
    GLint s;

   char log[512];


    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vs, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &s);
    if (!s)
    {
        glGetShaderInfoLog(vertex, 512, NULL, log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
    };


    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fs, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &s);
    if (!s)
    {
        glGetShaderInfoLog(fragment, 512, NULL, log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
    };

    shader->ID = glCreateProgram();
    glAttachShader(shader->ID, vertex);
    glAttachShader(shader->ID, fragment);
    glLinkProgram(shader->ID);

    glGetProgramiv(shader->ID, GL_LINK_STATUS, &s);
    if (!s)
    {
        glGetProgramInfoLog(shader->ID, 512, NULL, log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Win32UseShader(Shader *shader)
{
    glUseProgram(shader->ID);
}

const GLchar* Win32GetFsName(Shader *shader)
{
    return (shader->fs);
}

const GLchar* Win32GetVsName(Shader* shader)
{
    return (shader->vs);
}

void setBool(Shader *shader, const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(shader->ID, name.c_str()), (int)value);
}
void setInt(Shader *shader, const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(shader->ID, name.c_str()), value);
}
void setFloat(Shader *shader, const std::string name, float value)
{
    glUniform1f(glGetUniformLocation(shader->ID, name.c_str()), value);
}

void setVec2(Shader *shader, const std::string &name, const glm::vec2 &value)
{
    glUniform2fv(glGetUniformLocation(shader->ID, name.c_str()), 1, &value[0]);
}

void setVec2(Shader *shader, const std::string &name, float x, float y) 
{
    glUniform2f(glGetUniformLocation(shader->ID, name.c_str()), x, y);
}

void setVec3(Shader *shader, const std::string &name, const glm::vec3 &value) 
{
    glUniform3fv(glGetUniformLocation(shader->ID, name.c_str()), 1, &value[0]);
}

void setVec3(Shader *shader, const std::string &name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(shader->ID, name.c_str()), x, y, z);
}

void setVec4(Shader *shader, const std::string &name, const glm::vec4 &value) 
{
    glUniform4fv(glGetUniformLocation(shader->ID, name.c_str()), 1, &value[0]);
}
void setVec4(Shader *shader, const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(shader->ID, name.c_str()), x, y, z, w);
}

void setMat2(Shader *shader, const std::string &name, const glm::mat2 &mat) 
{
    glUniformMatrix2fv(glGetUniformLocation(shader->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void setMat3(Shader *shader, const std::string &name, const glm::mat3 &mat) 
{
    glUniformMatrix3fv(glGetUniformLocation(shader->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void setMat4(Shader *shader, const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}