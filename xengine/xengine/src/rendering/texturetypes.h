#pragma once

#include <glad/glad.h>

namespace XEngine
{
    enum TextureType
    {
        COLOR, HDR, GREYSCALE
    };

    enum Maps
    {
        FRAMEBUFFER = GL_FRAMEBUFFER,
        DEPTHATTACHMENT = GL_DEPTH_ATTACHMENT
    };
    
    enum TextureSampling
    {
        NONE,
        NEAREST,
        LINEAR
    };

    enum TextureWrapping
    {
        CLAMP = GL_CLAMP_TO_EDGE,
        REPEAT = GL_REPEAT,
        BORDER = GL_CLAMP_TO_BORDER
    };

    enum Channels
    {
        GREEN = GL_GREEN,
        BLUE = GL_BLUE,
        RED = GL_RED,
        RGB = GL_RGB,
        RGBA = GL_RGBA
    };

  /*  enum TextureWrapping
    {
        MIRRORED_REPEEAT = GL_MIRRORED_REPEAT,
        MIMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
        WRAP_S = GL_TEXTURE_WRAP_S,
        WRAP_T = GL_TEXTURE_WRAP_T,
        WRAP_R = GL_TEXTURE_WRAP_R,
        CLAMP = GL_CLAMP_TO_EDGE,
        REPEAT = GL_REPEAT,
        BORDER = GL_CLAMP_TO_BORDER,
        
    };

    enum TextureSampling
    {
        NONE,
        TEXTURE2D = GL_TEXTURE_2D,
        CUBETEXTURE = GL_TEXTURE_CUBE_MAP,
        MIN_FILTER = GL_TEXTURE_MIN_FILTER,
        MAG_FILTER = GL_TEXTURE_MAG_FILTER,
        NEAREST = GL_NEAREST,
        DEPTHTEX = GL_DEPTH_COMPONENT,
        LINEAR = GL_LINEAR,
        
    };*/
}