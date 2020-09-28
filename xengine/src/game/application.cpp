#ifndef APP_CPP
#define APP_CPP

#include "xengine/common.h"
#include "app_state.h"
#include "xengine/parser.h"
#include "xengine/opengl_loader.h"

//#include "xengine/graphics_device.h"
#include "xengine/layer.h"
#include "xengine/ecs.h"

#include "layers.h"

#include "xengine/math.cpp"
#include "xengine/string.cpp"
#include "xengine/parser.cpp"

#include "xengine/win32/win32_platform.cpp"
#include "xengine/containers.cpp"

#include "layers.cpp"

//global xe_graphics::GraphicsDevice *graphicsDevice = nullptr;

internal void InitGameLayers()
{
    Layer *layr2D = new Layer2D();
    Layer *layr3D = new Layer3D();

    DynArray<int> layersTest = createDynArray<int>();

    layersTest.push_back(1);
    layersTest.push_back(1745);

    Matrix4x4 world = createMat4x4();
    Vec3 pos = createVec3(0.0f, 5.0f, 1.0f);

}

APP_LOAD_DATA
{   
    p_state = ps;
   
    LoadAllOpenGLProcedures();

    InitGameLayers();
}

APP_UPDATE
{
    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);    
    //os->RefreshScreen();
}

#endif