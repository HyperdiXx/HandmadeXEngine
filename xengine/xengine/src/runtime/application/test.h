#pragma once
#ifndef TEST_H
#define TEST_H

#include <runtime/core/windowsystem/openglwindow.h>

class Test
{
public:
    Test() 
    {
        window = new XEngine::GLWindow("Game", 1280, 720);
    };

    void show() {};

private:
    XEngine::GLWindow * window = nullptr;
};


#endif // !TEST_H
