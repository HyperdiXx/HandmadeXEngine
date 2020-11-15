#ifndef APP_CPP
#define APP_CPP

#include "xengine\common.h"
#include "xengine\config.h"
#include "xengine\macro.h"

#include "xengine\math.cpp"
#include "xengine\containers.cpp"

#include "xengine\input.h"

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

//#include "xengine\tree.cpp"

#include "xengine\platform.h"

#ifdef GAPI_GL
    #include "xengine\graphics_context_gl.h"
    #include "xengine\graphics_context_gl.cpp"
    #include "xengine\graphics_device_gl.h"
    #include "xengine\graphics_device_gl.cpp"
#endif

#include "xengine\render.cpp"
#include "xengine\graphics_resource.cpp"
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
global Model *cube_model = nullptr;
global Vec3 light_pos = createVec3(-5.0f, -2.0f, 6.0f);

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
 
    /*Render::setupRenderCommand(CommandType::QUAD_COMMAND);
    Render::setupRenderCommand(CommandType::LINE_COMMAND);
  
    for (uint32 y = 15.0f; y < 700.0f; y += 25.0f)
    {
        for (uint32 x = 15.0f; x < 1250.0f; x += 25.0f)
        {
            Render::drawQuad(x, y, 20.0f, 20.0f, ColRGBA((x + 10) * 0.5f, y + 10, (y * 10) / 20.0f, 1.0f));
        }
    }

    Render::executeRenderCommand(CommandType::QUAD_COMMAND);
    Render::executeRenderCommand(CommandType::LINE_COMMAND);*/
 
    Render::beginRenderPass("deffered");

    Vec3 translationCharacter = createVec3(0.0f, -10.0f, -20.0f);
    Vec3 scaleCharacter = createVec3(0.5f, 0.5f, 0.5f);    
    Vec3 translationCube = createVec3(-5.0f, 0.0f, -10.0f);
    Vec3 scaleCube = createVec3(0.1f, 0.1f, 0.1f);

    Matrix4x4 modelMat = translateMat(translationCharacter) * scaleMat(scaleCharacter);

    Material *model_material = Render::getMaterial("base");
    Material *cube_material = Render::getMaterial("baseCube");
    Material *def = Render::getMaterial("deffered");

    Render::drawModel(nano_character, def, modelMat);

    modelMat = translateMat(translationCube) * scaleMat(scaleCube);
    Render::drawModel(cube_model, def, modelMat);

    Render::endRenderPass();
    
    Material *pp = Render::getMaterial("lightP");
    static bool32 isAdded = false;
    if (!isAdded)
    {
        Texture2D *albedo = Render::getTextureFromRenderPass("deffered", 2);
        Texture2D *normal = Render::getTextureFromRenderPass("deffered", 1);
        Texture2D *depth = Render::getTextureFromRenderPass("deffered", 4);
        
        pp->addTexture2D(albedo);
        pp->addTexture2D(normal);
        pp->addTexture2D(depth);

        isAdded = true;
    }

    Camera3D &camera3d = getCamera3D();

    pp->set("viewPos", ShaderUniformType::Vec3Uniform, &camera3d.pos);
    pp->set("lightPos", ShaderUniformType::Vec3Uniform, &light_pos);
    pp->set("view", ShaderUniformType::Mat4x4, &camera3d.getViewMatrix());
    pp->set("projection", ShaderUniformType::Mat4x4, &camera3d.getProjectionMatrix());

    Render::drawFullquad(pp);

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

    nano_character = loadModelFromFile("assets/nano/nanosuit.obj", false);
    cube_model = loadModelFromFile("assets/cube.obj", false);
    
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