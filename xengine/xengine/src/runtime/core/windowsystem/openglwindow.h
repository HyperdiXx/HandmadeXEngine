#pragma once

#ifndef INIT_H
#define INIT_H

#include <xenpch.h>
#include <types.h>
#include <input.h>
#include <perspective_camera.h>
#include <rendering/api/base/context.h>


namespace XEngine
{
    class GLWindow
    {
    public:
        GLWindow(const char* n, uint32 width, uint32 height);

        ~GLWindow();

        void update() const;
        void initStats();

        void setDepth();
        void setCullface();
        void setBlendFunc();
        void enableMultisample();
        void enableFramebufferSRGB();
        void destroy();

        bool32 isClosed();

        inline const uint32 getWidth() const { return m_width; };
        inline const uint32 getHeight() const { return m_height; };
        inline GLFWwindow *get_wind_ptr() { return m_window; };
    private:      
        void setVSYNC(bool set);
        void bindGLFW();

        void framebufferSizeCallback(GLFWwindow* window, int32 width, int32 height);
    private:
        
        const char* m_name;
        GLFWwindow* m_window;
        Rendering::DeviceContext* m_context;
        uint32 m_width, m_height;
        bool32 isRunning;
    };
}
#endif





