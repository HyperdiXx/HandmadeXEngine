#pragma once

#ifndef GLUIH
#define GLUIH

#include "ui.h"

#include <vector>

#include <vec4f.h>
#include <vec3f.h>

#include <glad/glad.h>


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
        void update(vec4f& spritecol);
        void setUIScene5(vec3f &pos, vec4f &color, unsigned int texture, vec4f &colo1, vec4f &clor2, vec4f color3, bool &pressed);
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


