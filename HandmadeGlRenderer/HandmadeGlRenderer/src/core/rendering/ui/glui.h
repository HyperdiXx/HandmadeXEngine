#pragma once

#ifndef GLUIH
#define GLUIH

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


namespace XEngine
{
    class GLGUI
    {
    public:
        GLGUI(GLFWwindow* win) : m_window(win)
        {
            init(win);
        }

        ~GLGUI()
        {
            shutdown();
        }

        void init(GLFWwindow* m_window);
        void startUpdate();
        void update(glm::vec4& spritecol);
        void shutdown();

        void setDarkTheme();
        void setLightTheme();
        void setClassicTheme();


    private:
        GLFWwindow* m_window;
    };
}


#endif // !GLUIH


