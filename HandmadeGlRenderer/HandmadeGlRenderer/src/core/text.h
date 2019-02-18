#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H  


#include <glm/glm.hpp>

#include "texture.h"
#include "../xenpch.h"
#include "shader.h"

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
    GLuint textVAO, textVBO;

    void InitSnt();
    void RenderSmth(Shader &shader, uint32 &VAO, std::string text, glm::vec3 color, uint32 x, uint32 y, uint32 scale);
    
}