#pragma once

#include "../core/rendering/renderType.h"

namespace XEngine
{
    class BaseApplication
    {
    public:

        BaseApplication() {};

        virtual void onStart() = 0;
        virtual void onUpdate(float dt) = 0;
        virtual void onPostUpdate() = 0;
        virtual void onDraw() = 0;
        virtual void onShutdown() = 0;

    };
}