#pragma once

#ifndef TEXTURE
#define TEXTURE

#include <glad/glad.h>
#include <stb_image.h>

enum TypeTexture
{
    REPEAT = GL_REPEAT,
    MIRRORED_REPEEAT = GL_MIRRORED_REPEAT,
    CLAMP_EDGE = GL_CLAMP_TO_EDGE,
    CLAMP_BORDER = GL_CLAMP_TO_BORDER
};


enum IntTexture
{

};

int loadTexture(const char* filename);


#endif // !TEXTURE

