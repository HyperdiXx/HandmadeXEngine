#pragma once


#ifndef INIT
#define INIT

#include "../core/types.h"
#include "../xenpch.h"
#include "../core/events/input.h"
#include "../core/cameras/camera.h"

namespace XEngine
{
    namespace Rendering
    {
        class WindowGL
        {
        public:
            const char* name;
            GLFWwindow* window;
            int32 w, h;
            bool isRunning;
            WindowGL(const char* n, int32 width, int32 height)
            {
                name = n;
                w = width;
                h = height;
                initGL();
            }
            ~WindowGL()
            {
                glfwTerminate();
            }
            
            void update() const;
            bool32 isClosed();
        private:
            void initGL();
            void initStats();
            void setVSYNC(bool set);
        };
    }
}

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