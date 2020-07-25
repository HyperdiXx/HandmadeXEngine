#pragma once

#ifndef LAYERS_H
#define LAYERS_H

#include "xe_layer.h"

namespace layer
{
    class Layer2D : public xe_graphics::Layer
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

    class Layer3D : public xe_graphics::Layer
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

    class GUILayer : public xe_graphics::Layer
    {
    public:

        void init();
        void render();
        void update(real32 dt);

    private:

    };
}

#endif // !LAYERS_H
