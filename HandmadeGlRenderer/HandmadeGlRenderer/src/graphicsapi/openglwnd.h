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
            const char* m_name;
            GLFWwindow* m_window;
            int32 m_w, m_h;
            bool isRunning;
            WindowGL(const char* n, int32 width, int32 height)
            {
                m_name = n;
                m_w = width;
                m_h = height;
                initGL();
            }
            ~WindowGL()
            {
                glfwTerminate();
            }
            
            void update() const;
            bool32 isClosed();

            inline int32 getWidth() const { return m_w; };
            inline int32 getHeight() const { return m_h; };

        private:
            void initGL();
            void initStats();
            void setVSYNC(bool set);
        };
    }
}

void mousecallback(GLFWwindow* window, real64 xpos, real64 ypos);
void framebufferSizeCallback(GLFWwindow* window, int32 width, int32 height);
#endif