#ifndef APP_CPP
#define APP_CPP

#include "xengine/common.h"
#include "app_state.h"
#include "xengine/parser.h"
#include "xengine/containers.h"
#include "xengine/opengl_loader.h"
//#include "xengine/graphics_device.h"
#include "xengine/layer.h"
#include "xengine/ecs.h"

#include "layers.h"

#include "xengine/string.cpp"
#include "xengine/parser.cpp"
#include "xengine/containers.cpp"

#include "layers.cpp"

//global xe_graphics::GraphicsDevice *graphicsDevice = nullptr;

internal void InitGameLayers()
{
    Layer *layr2D = new Layer2D();
    Layer *layr3D = new Layer3D();
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