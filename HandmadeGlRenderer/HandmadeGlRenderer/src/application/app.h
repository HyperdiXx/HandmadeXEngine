#pragma once


#include "../xenpch.h"

#include "../core/cameras/camera.h"

namespace XEngine
{

   
    class Application
    {
    public:
        void OpenGLRunEngineWin32();
        void InitStats();


        XEngine::Camera cam;
    };

}
