#ifndef APP_CPP
#define APP_CPP

#include "xengine\common.h"
#include "xengine\config.h"
#include "xengine\macro.h"

#include "xengine\math.cpp"
#include "xengine\string.cpp"
#include "xengine\containers.cpp"

#include "xengine\input.h"
#include "xengine\threading.h"
#include "app_state.h"

#include "xengine\utility.h"
#include "xengine\parser.h"
#include "xengine\opengl_loader.h"
#include "xengine\core.h"
#include "xengine\graphics_res_desc.h"
#include "xengine\graphics_resource.h"
#include "xengine\graphics_device.h"
#include "xengine\layer.h"
#include "xengine\ecs.h"
#include "xengine\audio.h"
#include "xengine\assets.h"
#include "xengine\asset_manager.h"
#include "xengine\render.h"
#include "xengine\memory.h"

#include "xengine\core.cpp"
#include "xengine\utility.cpp"
#include "xengine\parser.cpp"

//#include "xengine\tree.cpp"

#include "xengine\platform.h"

#ifdef GAPI_GL
    #include "xengine\graphics_context_gl.h"
    #include "xengine\graphics_context_gl.cpp"
    #include "xengine\graphics_device_gl.h"
    #include "xengine\graphics_device_gl.cpp"
#endif

#include "xengine\threading.cpp"
#include "xengine\render.cpp"
#include "xengine\graphics_resource.cpp"
#include "xengine\render_commands.cpp"
#include "xengine\memory.cpp"
#include "xengine\ecs.cpp"
#include "xengine\assets.cpp"
#include "xengine\asset_manager.cpp"

#include "layers.h"
#include "layers.cpp"

#include "game_state.h"
#include "game_state.cpp"

global DynArray<LayerTest> layersTest;
global DynArray<Rect> rects_to_test;
//global Quadtree tree;

global CubeMesh cube;
global Model *nano_character = nullptr;
global Model *cube_model = nullptr;

ResourceManager *resManager = ResourceManager::getInstance();

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
    
    //Layer2D *layr2D = (Layer2D*)allocateMemory(&arena, sizeof(Layer2D));    
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
void Render2D()
{
    Render::setupRenderCommand(CommandType::QUAD_COMMAND);
    Render::setupRenderCommand(CommandType::LINE_COMMAND);

    for (uint32 y = 15.0f; y < 700.0f; y += 25.0f)
    {
        for (uint32 x = 15.0f; x < 1250.0f; x += 25.0f)
        {
            Render::drawQuad(x, y, 20.0f, 20.0f, ColRGBA((x + 10) * 0.5f, y + 10, (y * 10) / 20.0f, 1.0f));
        }
    }

    Render::executeRenderCommand(CommandType::QUAD_COMMAND);
    Render::executeRenderCommand(CommandType::LINE_COMMAND);
}

internal 
void Render()
{
    Render::beginFrame();

    //Render2D();
    
    Render::beginRenderPass("deffered");

    Transform char_transf = {};

    char_transf.pos = createVec3(0.0f, -5.0f, -20.0f);
    char_transf.scale = createVec3(0.5f, 0.5f, 0.5f);

    Material *cube_material = Render::getMaterial("baseCube");
    Material *def = Render::getMaterial("deffered");
    Material *model_material = Render::getMaterial("base");

    RenderCommandStaticModel cmd(&char_transf, nano_character, def);
    cmd.execute();
    
    Transform cube_transf = {};

    cube_transf.pos = createVec3(-5.0f, 0.0f, -10.0f);
    cube_transf.scale = createVec3(0.1f, 0.1f, 0.1f);

    RenderCommandStaticModel drawCube(&cube_transf, cube_model, def);
    drawCube.execute();

    Render::endRenderPass();
    
    Material *light_pass_d = Render::getMaterial("lightP");
    RenderPass *deffered = Render::getRenderPass("deffered");

    PostProcPassCommand lighting_pass(light_pass_d, deffered);
    lighting_pass.execute();

    Render::endFrame();
}

APP_LOAD_DATA
{   
    platform_state = ps;
   
    asset_arena = createMemoryArena(0, 1024 * 1024 * 4);
   
    Vec4 red_colr = createVec4(1.0f, 0.0f, 0.0f, 1.0f);

    uint32 intClr = colorFromVec4(red_colr);

    Vec4 backClr = colorFromInt(intClr);


    ThreadPool::init();

    Render::init();
    
    std::vector<uint32> result = {};

    result.reserve(1024);

    ThreadPool::addTask([&result]
    {
        for (uint32 i = 0; i < 999; ++i)
        {
            result.push_back(i);
        }
    });

    ThreadPool::addTask([] 
    { 
        nano_character = resManager->getModel("assets/nano/nanosuit.obj", false); 
    });
    
    ThreadPool::addTask([] 
    { 
        cube_model = resManager->getModel("assets/cube.obj", false); 
    });
    
    InitGameLayers();

    //InitQuadTree();
    InitECS();

    // Executing already pushed render commands before drawing
    Render::endFrame();

    ThreadPool::wait();      

    for (uint32 i = 0; i < layersTest.size(); ++i)
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