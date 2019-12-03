#pragma once

#ifndef TESTAPP_H
#define TESTAPP_H

#include <runtime/core/windowsystem/openglwindow.h>


    class TestApp
    {
    public:

        TestApp();
        ~TestApp();
        void run();
      
        void onDraw();
        void onUpdate(float dt);
        void onPostUpdate();
        void onShutdown();

    private:
        XEngine::GLWindow *window = nullptr;
    };

#endif // !TESTAPP_H
