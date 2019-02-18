#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "../xenpch.h"


namespace XEngine
{

    struct Letter
    {
        GLuint id;
        glm::ivec2 Size;       
        glm::ivec2 Bearing;    
        GLuint     Advance;
    };


    std::map<GLchar, Letter> Characters;

    void InitSnt();
}