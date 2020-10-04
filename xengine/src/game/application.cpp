#ifndef APP_CPP
#define APP_CPP

#include "xengine\common.h"
#include "app_state.h"
#include "xengine\utility.h"
#include "xengine\parser.h"
#include "xengine\opengl_loader.h"
#include "xengine\math.cpp"

#include "xengine\config.h"

#include "xengine\core.h"
#include "xengine\graphics_res_desc.h"
#include "xengine\graphics_resource.h"
#include "xengine\graphics_device.h"
#include "xengine\render.h"
#include "xengine\layer.h"
#include "xengine\ecs.h"

#include "layers.h"
//#include "xengine\render.h"
#include "xengine\memory.h"

#include "xengine\core.cpp"
#include "xengine\utility.cpp"
#include "xengine\string.cpp"
#include "xengine\parser.cpp"

#include "xengine\win32\win32_platform.cpp"
#include "xengine\containers.cpp"

#ifdef GAPI_GL
    #include "xengine\graphics_device_gl.h"
    #include "xengine\graphics_device_gl.cpp"
#endif

#include "layers.cpp"
//#include "xengine\render.cpp"
#include "xengine\memory.cpp"

global GraphicsDevice *graphicsDevice = 0;
global MemoryArena arena;
global DynArray<LayerTest> layersTest;

internal void InitGameLayers()
{
    LayerTest t1 = {};

    t1.type = LayerType::LAYER_2D;
    t1.Init = Layer2DInit;
    t1.Update = Layer2DUpdate;

    LayerTest t2 = {};

    t2.type = LayerType::LAYER_3D;
    t2.Init = Layer3DInit;
    t2.Update = Layer3DUpdate;

    LayerTest guiT= {};

    guiT.type = LayerType::GUI;
    guiT.Init = LayerGUIInit;
    guiT.Update = LayerGUIUpdate;

    Layer2D *layr2D = (Layer2D*)allocateMemory(&arena, sizeof(Layer2D));    
    //Layer *lar3D = (Layer3D*)allocateMemory(&arena, sizeof(Layer3D));

    //Layer *layr3D = new Layer3D();

    layersTest = createDynArray<LayerTest>();

    layersTest.push_back(t1);
    layersTest.push_back(t2);
    layersTest.push_back(guiT);

    Matrix4x4 world = createMat4x4();
    Vec3 pos = createVec3(0.0f, 5.0f, 1.0f);
}

APP_LOAD_DATA
{   
    platform_state = ps;
   
    LoadAllOpenGLProcedures();

    switch (platform_state->render_api)
    {
    case PlatformState::RenderApi::OPENGL:
    {
         graphicsDevice = new GraphicsDeviceGL();



    } break;
    case PlatformState::RenderApi::DX11:
    {

    } break;
    }
        
   

    arena = createMemoryArena(0, 1024 * 1024 * 4);

    InitGameLayers();


    for (int i = 0; i < layersTest.size(); ++i)
    {
        LayerTest *lay = layersTest.begin() + i;
        lay->Init();
    }
}

APP_UPDATE
{
    graphicsDevice->clearColor(0.7f, 0.7f, 0.9f, 1.0f);
    graphicsDevice->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update Layers

    for (int i = 0; i < layersTest.size(); ++i)
    {
        LayerTest *lay = layersTest.begin() + i;
        lay->Update(0.016f);
    }

    //os->RefreshScreen();
}

#endif