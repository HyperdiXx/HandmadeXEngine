#pragma once


#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../types.h"

namespace XEngine
{
    static uint32 cubeVAO = 0;
    static uint32 cubeVBO = 0;
    static uint32 quadVAO = 0;
    static uint32 quadVBO;

    void renderCube();
    void renderRect();
    void renderQuad();

}




