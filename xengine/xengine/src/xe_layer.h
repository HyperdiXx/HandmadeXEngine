#pragma once

#ifndef XE_LAYER_H
#define XE_LAYER_H

#include "types.h"
#include "xenpch.h"

#include "xe_ecs.h"

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
    public:
        Layer2D() {};
        ~Layer2D() {};

        void init() override;
        void render() override;
        void update(real32 dt) override;

        void addEntity(xe_ecs::Entity* ent);
    private:
        std::vector<xe_ecs::Entity> entities;
    };

    class Layer3D : public Layer
    {
    public:
        Layer3D() {};
        ~Layer3D() {};

        void init() override;
        void render() override;
        void update(real32 dt) override;

        void addEntity(xe_ecs::Entity* ent);
    private:
        std::vector<xe_ecs::Entity> entities;
    };

    class GUILayer
    {
    public:
        void init();
        void render();
        void update(real32 dt);

    private:

    };
}
#endif // !XE_LAYER_H

