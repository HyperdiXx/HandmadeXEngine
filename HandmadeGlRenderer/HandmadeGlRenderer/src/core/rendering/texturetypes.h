#pragma once

#include <glad/glad.h>

namespace XEngine
{
    enum Maps
    {
        FRAMEBUFFER = GL_FRAMEBUFFER,
        DEPTHATTACHMENT = GL_DEPTH_ATTACHMENT
    };

    enum Channels
    {
        GREEN = GL_GREEN,
        BLUE = GL_BLUE,
        RED = GL_RED,
        RGB = GL_RGB,
        RGBA = GL_RGBA
    };

    enum TypeTexture
    {
        TEXTURE2D = GL_TEXTURE_2D,
        CUBETEXTURE = GL_TEXTURE_CUBE_MAP,
        REPEAT = GL_REPEAT,
        MIRRORED_REPEEAT = GL_MIRRORED_REPEAT,
        CLAMP_EDGE = GL_CLAMP_TO_EDGE,
        CLAMP_BORDER = GL_CLAMP_TO_BORDER,
        LINEAR = GL_LINEAR,
        WRAP_S = GL_TEXTURE_WRAP_S,
        WRAP_T = GL_TEXTURE_WRAP_T,
        WRAP_R = GL_TEXTURE_WRAP_R,
        MIN_FILTER = GL_TEXTURE_MIN_FILTER,
        MAG_FILTER = GL_TEXTURE_MAG_FILTER,
        MIMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
        NEAREST = GL_NEAREST,
        DEPTHTEX = GL_DEPTH_COMPONENT
    };
}