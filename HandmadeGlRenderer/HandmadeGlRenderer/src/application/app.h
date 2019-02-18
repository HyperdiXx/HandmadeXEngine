#pragma once

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


struct Loop
{
    Shader basicShader;
    Shader lightShader;
    Shader cubeMap;
    Shader floorShader;
    real32 deltaTime = 0.0f;
    real32 lastFrame = 0.0f;
};

void RunEngineWin32();
void UpdateLoopWin32(WindowBuffer *wb, XEngine::Camera *cam, Loop *lp);
void InitStats();
void RenderQ();