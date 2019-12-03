#pragma once

#ifndef INIT_H
#define INIT_H

#include <xenpch.h>
#include <runtime/types.h>
#include <runtime/core/events/input.h>
#include <runtime/core/cameras/perspectivecamera.h>
#include <runtime/core/rendering/api/base/context.h>


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

        bool32 isClosed();

        inline const uint32 getWidth() const { return m_width; };
        inline const uint32 getHeight() const { return m_height; };

    private:      
        void setVSYNC(bool set);
        void bindGLFW();

        void framebufferSizeCallback(GLFWwindow* window, int32 width, int32 height);
    private:
        
        const char* m_name;
        GLFWwindow* m_window;
        Rendering::Context* m_context;
        uint32 m_width, m_height;
        bool32 isRunning;
    };
}
#endif





