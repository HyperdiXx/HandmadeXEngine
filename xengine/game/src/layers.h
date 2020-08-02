#pragma once

#ifndef LAYERS_H
#define LAYERS_H

#include "xe_layer.h"
#include "render_pass.h"

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

        void addEntity(xe_ecs::Entity ent);
    private:
        std::vector<xe_ecs::Entity> entities;
        xe_ecs::Entity main_ent;
    };

    class Layer3D : public xe_graphics::Layer
    {
    public:
        Layer3D() {};
        ~Layer3D() {};

        void init() override;
        void render() override;
        void update(real32 dt) override;

        void addEntity(xe_ecs::Entity ent);
    private:
        std::vector<xe_ecs::Entity> entities;

        xe_graphics::RenderPass *render_pass;
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
