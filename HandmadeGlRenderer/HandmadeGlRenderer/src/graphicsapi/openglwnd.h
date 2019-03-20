#pragma once


#ifndef INIT
#define INIT

#include "../core/types.h"
#include "../application/xenpch.h"
#include "../core/events/input.h"
#include "../core/cameras/camera.h"



//class  WindowGL
//{
//public:
//
//    WindowGL()
//    {
//        
//    }
//
//    ~WindowGL()
//    {
//
//    }
//
//    
//   
//
//    
//};

struct __declspec(dllexport) OpenGLWindow
{
    GLFWwindow* window;
    int32 w, h;
};

void __declspec(dllexport) InitOpenglWindow(OpenGLWindow *wb);
void __declspec(dllexport) setVSYNC(bool set);
void mousecallback(GLFWwindow* window, real64 xpos, real64 ypos);
void framebufferSizeCallback(GLFWwindow* window, int32 width, int32 height);

#endif