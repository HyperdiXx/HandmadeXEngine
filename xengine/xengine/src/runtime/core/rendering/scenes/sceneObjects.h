#pragma once

#include "../../rendering/api/opengl/glframebuffer.h"
#include <xenpch.h>


namespace XEngine
{

    class SceneObjects
    {
    public:

        glm::vec3 fogColor;

        real32 deltaTime = 0.0f;
        real32 lastFrame = 0.0f;

        glm::mat4 projMatrix = glm::mat4(1.0f);

        Rendering::FrameBuffer *sceneFBO;
        bool wireframe = false;
    public:
        static SceneObjects& getInstance()
        {
            static SceneObjects instance;
            return instance;
        }
    };

}