#pragma once

#ifndef LAYERS_H
#define LAYERS_H

//#include "render_pass.h"

class Layer2D
{
public:
    Layer2D() {};
    ~Layer2D() {};

    void init();
    void render();
    void update(real32 dt);

    void addEntity(Entity ent);
private:
    std::vector<Entity> entities;
    Entity main_ent;
};

class Layer3D
{
public:
    Layer3D() {};
    ~Layer3D() {};

    void init();
    void render();
    void update(real32 dt);

    void addEntity(Entity ent);
private:
    std::vector<Entity> entities;

    //RenderPass *render_pass;
};

class GUILayer
{
public:

    void init();
    void render();
    void update(real32 dt);

private:

};

struct LayerTest
{
    enum class LayerType
    {
        LAYER_2D,
        LAYER_3D,
        GUI
    };

    LayerTest() {};
    LayerTest(LayerTest &&test) {};

    ~LayerTest() {};
    LayerType type;

    union
    {
        Layer2D layer2D;
        Layer3D layer3D;
        GUILayer guiLayer;
    };
};

#endif // !LAYERS_H
