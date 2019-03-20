#pragma once

#include "allxengine.h"

namespace XEngine
{
    class Application
    {
    public:
        Application()
        {

        }

        ~Application()
        {

        }

        void OpenGLRunEngineWin32();
        void InitStats();
        void RenderQ(Shader *shader);
       
        FlyCamera cam;
    };

}
