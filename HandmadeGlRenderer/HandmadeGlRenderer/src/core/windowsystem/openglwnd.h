#pragma once


#ifndef INIT
#define INIT

#include "../types.h"
#include "../../xenpch.h"
#include "../../core/events/input.h"
#include "../cameras/camera.h"



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
               
            }
            
            void update() const;
            void initStats();

            void setDepth();
            void setCullface();
            void setBlendFunc();
            void enableMultisample();

          
            bool32 isClosed();

            inline const int32 getWidth() const { return m_w; };
            inline const int32 getHeight() const { return m_h; };


        private:
            void initGL(); 
            void setVSYNC(bool set);
        };
    }

    

    void framebufferSizeCallback(GLFWwindow* window, int32 width, int32 height);


}
#endif





