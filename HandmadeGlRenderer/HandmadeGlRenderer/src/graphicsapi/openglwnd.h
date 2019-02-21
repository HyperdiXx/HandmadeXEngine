#pragma once
#ifndef INIT
#define INIT

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../core/types.h"
#include "../xenpch.h"
#include "../core/input.h"
#include "../core/camera.h"

const uint32 WIDTH = 1280;
const uint32 HEIGHT = 720;

struct WindowBuffer
{
    GLFWwindow* window;
    int32 w, h;
};


void InitOpenglWindow(WindowBuffer *buffer);
void setVSYNC(bool set);
void mousecallback(GLFWwindow* window, real64 xpos, real64 ypos);
void framebufferSizeCallback(GLFWwindow* window, int32 width, int32 height);
#endif