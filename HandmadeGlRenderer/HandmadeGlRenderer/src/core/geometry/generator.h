#pragma once


#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../types.h"
#include <vector>

namespace XEngine
{
    static uint32 cubeVAO = 0;
    static uint32 cubeVBO = 0;
    static uint32 quadVAO = 0;
    static uint32 quadVBO;
    static uint32 sphereVAO = 0;
    static uint32 indexCount;

    void renderCube();
    void renderSphere();
    void renderRect();
    void renderQuad();
    std::vector<float> createPlane();
    std::vector<float> createVert();


}




