#pragma once

#include "baseapp.h"

#include "../core/cameras/camera.h"


namespace XEngine
{

    class TestApp : public BaseApplication
    {
    public:

        TestApp(RenderAPI type);

        void onStart();
        void onDraw();
        void onUpdate(float dt);
        void onPostUpdate();
        void onShutdown();

    private:

        bool32 isRunning;
        

    };

}
