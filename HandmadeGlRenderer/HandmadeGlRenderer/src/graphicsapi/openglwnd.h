#pragma once
#ifndef INIT
#define INIT

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../core/types.h"
#include <iostream>

const uint32 WIDTH = 1280;
const uint32 HEIGHT = 720;

struct WindowBuffer
{
    GLFWwindow* window;
    int32 w, h;
};

struct Camera
{
    glm::vec3 camPos;
    glm::vec3 camTarget;
    glm::vec3 camUp;
    real32 speed; 
};

void InitOpenglWindow(WindowBuffer *buffer);
void processInput(GLFWwindow* window, Camera *cam);
//void mousecallback(GLFWwindow* window, real64 xpos, real64 ypos);
void framebufferSizeCallback(GLFWwindow* window, int32 width, int32 height);
#endif