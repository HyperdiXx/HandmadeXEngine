#pragma once

#ifndef TEXTURE
#define TEXTURE

#include "../../application/xenpch.h"
#include "../types.h"



namespace XEngine
{
    enum __declspec(dllexport) Maps
    {
        FRAMEBUFFER = GL_FRAMEBUFFER,
        DEPTHATTACHMENT = GL_DEPTH_ATTACHMENT
    };

    enum __declspec(dllexport) Channels
    {
        GREEN = GL_GREEN,
        BLUE = GL_BLUE,
        RED = GL_RED,
        RGB = GL_RGB,
        RGBA = GL_RGBA
    };

    enum __declspec(dllexport) TypeTexture
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

    struct __declspec(dllexport) Cubemap
    {
        uint32 ID;
        uint32 w, h, channels;
        unsigned char *data;

        std::vector<std::string> textures;
    };

   
    uint32 __declspec(dllexport) loadCubemap(std::vector<std::string> textures);
    int __declspec(dllexport) loadTexture(const char* filename);
    uint32 __declspec(dllexport) loadtexture2DFromDir(const std::string path, const std::string &dir, bool gamma);

    void __declspec(dllexport) bindTexture2D(uint16 n, uint32 tex1);
    void __declspec(dllexport) bindCubeTexture2D(uint16 n, uint32 tex1);
    void __declspec(dllexport) setDepthFunc(int n);
}


#endif // !TEXTURE

