#pragma once

#ifndef XE_LAYER_H
#define XE_LAYER_H

#include "types.h"

namespace xe_graphics
{
    class Layer
    {
    public:

        virtual ~Layer() {}

        virtual void init() = 0;

        virtual void render() = 0;

        virtual void update(real32 dt) = 0;

    };

    class Layer2D : public Layer
    {

    };

    class Layer3D : public Layer
    {

    };

    class GUILayer : public Layer
    {
    public:

        void init() override;

        void render() override;

        void update(real32 dt) override;
    };
}
#endif // !XE_LAYER_H

