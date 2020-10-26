#ifndef APP_CPP
#define APP_CPP

#include "xengine\common.h"
#include "xengine\config.h"

#include "xengine\math.cpp"
#include "xengine\containers.cpp"

#include "app_state.h"
#include "game_state.h"

#include "xengine\utility.h"
#include "xengine\parser.h"
#include "xengine\opengl_loader.h"
#include "xengine\core.h"
#include "xengine\graphics_res_desc.h"
#include "xengine\graphics_resource.h"
#include "xengine\graphics_device.h"
#include "xengine\layer.h"
#include "xengine\ecs.h"
#include "xengine\assets.h"
#include "xengine\render.h"
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

#include "xengine\graphics_resource.cpp"
#include "xengine\render.cpp"
#include "xengine\memory.cpp"
#include "xengine\ecs.cpp"
#include "xengine\assets.cpp"

#include "layers.h"
#include "layers.cpp"

#include "game_state.cpp"

global MemoryArena arena;
global DynArray<LayerTest> layersTest;
global DynArray<Rect> rects_to_test;
//global Quadtree tree;

global CubeMesh cube;
global Model *nano_character = nullptr;

internal 
void InitGameLayers()
{
    layersTest = createDynArray<LayerTest>();

    LayerTest t1 = {};
    t1.type = LayerTest::LayerType::LAYER_2D;
    
    LayerTest t2 = {};
    t2.type = LayerTest::LayerType::LAYER_3D;
    
    LayerTest guiT= {};
    guiT.type = LayerTest::LayerType::GUI;
    
    Layer2D *layr2D = (Layer2D*)allocateMemory(&arena, sizeof(Layer2D));    
    //Layer *lar3D = (Layer3D*)allocateMemory(&arena, sizeof(Layer3D));

    //Layer *layr3D = new Layer3D();
    
    //layersTest.push_back(std::move(t1));
    //layersTest.push_back(std::move(t2));
    //layersTest.push_back(std::move(guiT));
}

internal
void InitQuadTree()
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

internal 
void InitECS()
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

internal 
void UpdateLayers()
{
    // Update Layers

    for (int i = 0; i < layersTest.size(); ++i)
    {
    //   LayerTest *lay = layersTest.begin() + i;
    //   lay->Update(0.016f);
    }
}

internal 
void Render()
{
    Render::beginFrame();

    Render::setupRenderCommand(CommandType::QUAD_COMMAND);
    Render::setupRenderCommand(CommandType::LINE_COMMAND);

    //Render::drawCube(); 
    //Render::drawTriangle();

    for (uint32 y = 15.0f; y < 700.0f; y += 25.0f)
    {
        for (uint32 x = 15.0f; x < 1250.0f; x += 25.0f)
        {
            Render::drawQuad(x, y, 20, 20, Color4RGBA((x + 10) * 0.5f, y + 10, (y * 10) / 20.0f, 1.0f));
        }
    }

    Render::executeRenderCommand(CommandType::QUAD_COMMAND);
    Render::executeRenderCommand(CommandType::LINE_COMMAND);
    
    Matrix4x4 base = createMat4x4();
    Vec3 translation = createVec3(0.0f, 0.0f, -50.0f);
    translateMat(base, translation);

    Shader *d3shader = Render::getShader("base3d");
    Render::drawModel(nano_character, d3shader, base);

    //Render::endFrame();
}

APP_LOAD_DATA
{   
    platform_state = ps;
   
    Render::init();

    arena = createMemoryArena(0, 1024 * 1024 * 4);

    InitGameLayers();

    //InitQuadTree();
    InitECS();

    nano_character = loadModelFromFile("assets/nano/nanosuit.obj");

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
    WindowOptions &win_options = platform_state->options.window_options;

    if (win_options.resized)
    {
        Render::viewport(win_options.window_width, win_options.window_height);

        win_options.resized = false;       
    }

    UpdateLayers();
    Render();
}

#endif