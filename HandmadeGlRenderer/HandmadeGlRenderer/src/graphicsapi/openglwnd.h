#pragma once


#ifndef INIT
#define INIT

#include "../core/types.h"
#include "../xenpch.h"
#include "../core/events/input.h"
#include "../core/cameras/camera.h"


struct OpenGLWindowBuffer
{
    GLFWwindow* window;
    int32 w, h;
};


void InitOpenglWindow(OpenGLWindowBuffer *buffer);
void setVSYNC(bool set);
void mousecallback(GLFWwindow* window, real64 xpos, real64 ypos);
void framebufferSizeCallback(GLFWwindow* window, int32 width, int32 height);
#endif