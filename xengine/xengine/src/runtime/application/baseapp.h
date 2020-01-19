#pragma once

#ifndef BASEAPP_H
#define BASEAPP_H

#include <runtime/core/rendering/render/render.h>

namespace XEngine
{  
    class BaseApplication
    {
    public:

        virtual ~BaseApplication() = default;

        virtual void onUpdate(float dt) = 0;
        virtual void onPostUpdate() = 0;
        virtual void onDraw() = 0;
        virtual void onShutdown() = 0;
    private:



    };
}
#endif // !BASEAPP_H
