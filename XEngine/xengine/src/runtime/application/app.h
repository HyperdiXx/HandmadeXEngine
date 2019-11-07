#pragma once

#ifndef APP_INIT
#define APP_INIT

namespace XEngine
{
    struct Application
    {
        void OpenGLScene1();
        void OpenGLScene2();
        void OpenGLScene3();
        void OpenGLScene4();
        void OpenGLScene5();
        void terrainDemo();

        void pbr();

        void updateloop();
        void render();

        void DX11InitEngine();    
    };
}

#endif