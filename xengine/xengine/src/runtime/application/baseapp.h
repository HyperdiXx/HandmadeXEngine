#pragma once
#ifndef BASEAPP_H
#define BASEAPP_H

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
    };
}
#endif // !BASEAPP_H
