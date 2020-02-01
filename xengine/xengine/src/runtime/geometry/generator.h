#pragma once

#include <types.h>
#include "model.h"

namespace XEngine
{
    static uint32 cubeVAO = 0;
    static uint32 cubeVBO = 0;
    static uint32 quadVAO = 0;
    static uint32 quadVBO;
    static uint32 sphereVAO = 0;
    static uint32 indexCount;
 
    std::vector<float> createPlane();
    std::vector<float> createVert();

    class Geometry
    {
    public:
        std::map<std::string, Assets::Model*> models;

        std::string cube = "src/models/simple/cube.obj";
        std::string sphere = "src/models/simple/sphere.obj";
        std::string plane = "src/models/simple/plane.obj";

        static void renderCube();
        static void renderSphere();
        static void renderRect();
        static void renderQuad();
    };
}




