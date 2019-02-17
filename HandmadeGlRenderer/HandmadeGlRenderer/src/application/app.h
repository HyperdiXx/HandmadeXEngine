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


void InitEngineWin32();
void UpdateLoopWin32();
void InitStats();
void RenderLoop();