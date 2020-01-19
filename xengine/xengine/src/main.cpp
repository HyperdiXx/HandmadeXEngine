
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

        SceneManager, Stack Linked List

        DX11 ...
        DX12 ...


        Scene 1: Objects, plane, shadows, Dynamic dirLight, Spray Particles
        Scene 2: PBR, IBL
        Scene 3: Sky, Volumetric clouds, terrain

*/

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <math/xemath.h>

#include <runtime/application/testapp.h>

#define DEBUG

#ifdef DEBUG
    int main()
    {
        using namespace XEngine;
        
        TestApp testapp;

        testapp.run();

        return (0);
    }
#else
{
    int CALLBACK
    WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR lp_cmd_line, int n_show_cmd)
    {
        using namespace XEngine;

        TestApp *testapp = new TestApp();

        testapp->run();

        delete testapp;
        testapp = nullptr;

        return (0);
    }
}
#endif // DEBUG

