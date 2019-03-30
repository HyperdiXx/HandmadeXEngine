#pragma once

#ifndef GLUIH
#define GLUIH

#include "ui.h"

namespace XEngine
{
    class GLGUI : public UserInterface
    {
    public:

        GLGUI(GLFWwindow* win, int theme) : m_window(win)
        {
            init(win, theme);
        }

        ~GLGUI()
        {
            shutdown();
        }

        void init(GLFWwindow* window, int theme);
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


