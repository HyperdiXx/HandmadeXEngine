#pragma once

#ifndef GLUIH
#define GLUIH

#include "ui.h"

#include <vector>

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
           
        }

        void init(GLFWwindow* window, int theme);
        void startUpdate();
        void update(glm::vec4& spritecol);
        void setUIScene5(glm::vec3 &pos);
        //void addEdit3();
        void shutdown();

        void setDarkTheme();
        void setLightTheme();
        void setClassicTheme();


    private:
        GLFWwindow* m_window;
        std::vector<int> editLayer;
    };
}


#endif // !GLUIH


