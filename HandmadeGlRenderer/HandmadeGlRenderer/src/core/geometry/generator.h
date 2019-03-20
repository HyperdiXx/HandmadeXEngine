#pragma once


#include "../../application/xenpch.h"
#include "../types.h"


namespace XEngine
{
    static uint32 cubeVAO = 0;
    static uint32 cubeVBO = 0;
    static uint32 quadVAO = 0;
    static uint32 quadVBO;

    void __declspec(dllexport) renderCube();
    void __declspec(dllexport) renderRect();
    void __declspec(dllexport) renderQuad();
    std::vector<float> __declspec(dllexport) createPlane();
    std::vector<float> __declspec(dllexport) createVert();
}




