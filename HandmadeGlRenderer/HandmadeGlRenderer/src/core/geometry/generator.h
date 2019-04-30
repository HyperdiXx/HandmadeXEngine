#pragma once


#include <glm/glm.hpp>
#include <glad/glad.h>

#include "model.h"

#include "../types.h"
#include <vector>
#include <map>

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

    class Geometry
    {
    public:
        std::map<std::string, Assets::Model*> models;

        std::string cube = "src/models/simple/cube.obj";
        std::string sphere = "src/models/simple/sphere.obj";
        std::string plane = "src/models/simple/plane.obj";

    };




}




