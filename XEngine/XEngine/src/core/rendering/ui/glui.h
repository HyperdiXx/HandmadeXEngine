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
        void setUIScene5(glm::vec3 &pos, glm::vec4 &color, unsigned int texture, glm::vec4 &colo1, glm::vec4 &clor2, glm::vec4 color3, bool &pressed);
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


