
/*
    XEngine.
    OpenGL API 4.5
    DX11

    Features: Camera, ImGUI, Textures, MultiTextures, Lighting, Redering Interfaces, FrameBuffers, Cubemap, MSAA, ForwardShading, DefferedShading, Stencil, Blending, PostProcess,
    FaceCulling, Instancing, DynamicShadowMapping + DirLight, OmniLightsShadows, NormalMapping, ParallaxMapping,  Antialiasing, Gamma Correctiom
    TODO(vlad): Assimp, Logger, 
        
        
        Bloom,
        HDR, SSAO, PBR, IBL
        Spray Particles, Skinning

        SceneManager, Stack Linked List, Materials, struct Entity, Scene, Transformation

        DX11 ...
        DX12 ...
*/



#include <thread>
#include <future>

#include "application/app.h"

#define OPENGL

int main(int argc, char** argv)
{
    using namespace XEngine;

    Application *testapp = (Application*)malloc(sizeof(Application));
#ifdef  OPENGL
    testapp->terrainDemo();
#else
    testapp->DX11InitEngine();
#endif 

    free(testapp);


    return (0);
}


