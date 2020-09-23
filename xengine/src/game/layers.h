#pragma once

#ifndef LAYERS_H
#define LAYERS_H

//#include "render_pass.h"

class Layer2D : public Layer
{
public:
    Layer2D() {};
    ~Layer2D() {};

    void init() override;
    void render() override;
    void update(real32 dt) override;

    void addEntity(Entity ent);
private:
    std::vector<Entity> entities;
    Entity main_ent;
};

class Layer3D : public Layer
{
public:
    Layer3D() {};
    ~Layer3D() {};

    void init() override;
    void render() override;
    void update(real32 dt) override;

    void addEntity(Entity ent);
private:
    std::vector<Entity> entities;

    //RenderPass *render_pass;
};

class GUILayer : public Layer
{
public:

    void init();
    void render();
    void update(real32 dt);

private:

};

#endif // !LAYERS_H
