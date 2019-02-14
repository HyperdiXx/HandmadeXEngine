#pragma once

#ifndef TEXTURE
#define TEXTURE

#include <glad/glad.h>
#include <stb_image.h>
#include "../xenpch.h"
#include "types.h"

namespace XEngine
{
    enum TypeTexture
    {
        REPEAT = GL_REPEAT,
        MIRRORED_REPEEAT = GL_MIRRORED_REPEAT,
        CLAMP_EDGE = GL_CLAMP_TO_EDGE,
        CLAMP_BORDER = GL_CLAMP_TO_BORDER
    };

    struct Cubemap
    {
        uint32 ID;
        uint32 w, h, channels;
        unsigned char *data;

        std::vector<std::string> textures;
    };


    enum IntTexture
    {

    };


   
    uint32 loadCubemap(Cubemap *c);
    int loadTexture(const char* filename);



}


#endif // !TEXTURE

