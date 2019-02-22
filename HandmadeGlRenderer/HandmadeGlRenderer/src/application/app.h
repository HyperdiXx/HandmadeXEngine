#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H  
#define GLEW_STATIC

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../graphicsapi/openglwnd.h"
#include "../core/shader.h"
#include "../core/texture.h"
#include "../core/model.h"
#include "../core/imguibase.h"
#include "../core/camera.h"



#include <iostream>

namespace XEngine
{
    struct Loop
    {
        Shader basicShader;
        Shader lightShader;
        Shader cubeMap;
        Shader floorShader;
        real32 deltaTime = 0.0f;
        real32 lastFrame = 0.0f;
    };

    struct Letter
    {
        GLuint id;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        GLuint     Advance;
    };


   

    void RunEngineWin32();
    void UpdateLoopWin32();
    void InitStats();
    void RenderQ(Shader *shader);
}
