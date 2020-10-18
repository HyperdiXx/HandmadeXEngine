#ifndef APP_CPP
#define APP_CPP

#include "xengine\common.h"
#include "app_state.h"
#include "xengine\utility.h"
#include "xengine\parser.h"
#include "xengine\opengl_loader.h"
#include "xengine\config.h"
#include "xengine\containers.cpp"
#include "xengine\math.cpp"

#include "xengine\core.h"
#include "xengine\graphics_res_desc.h"
#include "xengine\graphics_resource.h"
#include "xengine\graphics_device.h"
#include "xengine\layer.h"
#include "xengine\ecs.h"
#include "xengine\render.h"

#include "layers.h"
#include "xengine\memory.h"

#include "xengine\core.cpp"
#include "xengine\utility.cpp"
#include "xengine\string.cpp"
#include "xengine\parser.cpp"

#include "xengine\win32\win32_platform.cpp"

//#include "xengine\tree.cpp"

#ifdef GAPI_GL
    #include "xengine\graphics_device_gl.h"
    #include "xengine\graphics_device_gl.cpp"
#endif

#include "layers.cpp"
#include "xengine\render.cpp"
#include "xengine\memory.cpp"
#include "xengine\ecs.cpp"

global MemoryArena arena;
global DynArray<LayerTest> layersTest;
global DynArray<Rect> rects_to_test;
//global Quadtree tree;

global DynArray<Component> components;
global DynArray<System> systems;

global CubeMesh cube;

internal void InitGameLayers()
{
    LayerTest t1 = {};

    t1.type = LayerTest::LayerType::LAYER_2D;
    
    LayerTest t2 = {};

    t2.type = LayerTest::LayerType::LAYER_3D;
    
    LayerTest guiT= {};

    guiT.type = LayerTest::LayerType::GUI;
    
    Layer2D *layr2D = (Layer2D*)allocateMemory(&arena, sizeof(Layer2D));    
    //Layer *lar3D = (Layer3D*)allocateMemory(&arena, sizeof(Layer3D));

    //Layer *layr3D = new Layer3D();

    //layersTest = createDynArray<LayerTest>();

    //layersTest.push_back(std::move(t1));
    //layersTest.push_back(std::move(t2));
    //layersTest.push_back(std::move(guiT));

    Matrix4x4 world = createMat4x4();
    Vec3 pos = createVec3(0.0f, 5.0f, 1.0f);
}

internal void InitQuadTree()
{
    /*tree = Quadtree(0, 0, 1280, 720, 0, 4);

    rects_to_test = createDynArray<Rect>();

    rects_to_test.push_back(createRect(25, 25, 100, 100));
    rects_to_test.push_back(createRect(250, 250, 100, 100));
    rects_to_test.push_back(createRect(500, 500, 100, 100));
    rects_to_test.push_back(createRect(750, 750, 100, 100));

    for (int i = 0; i < 4; ++i)
    {
        Rect cur = rects_to_test.at(i);
        addObject(&tree, &cur);
    }*/
}

internal void InitECS()
{
    System base_s(convertToSystemType("TransformSystem"));
    System render_s(convertToSystemType("RenderSystem"));
 
    ECSManager ecs = {};

    Entity tetsEnt = ecs.createEntity();
    
    ecs.removeEntity();
    
    ecs.createSystem(base_s);
    ecs.createSystem(render_s);

    ecs.updateSystems();
}

APP_LOAD_DATA
{   
    platform_state = ps;
   
    Render::init();

    arena = createMemoryArena(0, 1024 * 1024 * 4);

    InitGameLayers();

    //InitQuadTree();
    InitECS();

    for (int i = 0; i < layersTest.size(); ++i)
    {
        LayerTest *layer = layersTest.begin() + i;
        
        switch (layer->type)
        {
        case LayerTest::LayerType::LAYER_2D:
        {
            layer->layer2D.init();
        } break;
        
        default:
            break;
        }

    }
}

APP_UPDATE
{
    Render::clearColor(0.7f, 0.7f, 0.9f, 1.0f);
    Render::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Render::drawCube();

    //Render::drawTriangle();

    // Update Layers

    //for (int i = 0; i < layersTest.size(); ++i)
    //{
    //    LayerTest *lay = layersTest.begin() + i;
    //   lay->Update(0.016f);
    //}

    Render::executeCommands();

    //os->RefreshScreen();
}

#endif