#pragma once

#ifndef SHADER_TYPE
#define SHADER_TYPE

#include <glad/glad.h>

namespace XEngine
{
    enum GLShaderType
    {
        VertexShader = GL_VERTEX_SHADER,
        GeometryShader = GL_GEOMETRY_SHADER,
        FragmentShader = GL_FRAGMENT_SHADER
    };
}
#endif // !SHADER_TYPE


