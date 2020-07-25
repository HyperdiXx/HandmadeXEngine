
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

// Engine 

#include <xengine.h>

#include "app_state.h"

/*#include "xe_platform.h"
#include <math/xemath.h>
#include "xe_config.h"
#include "xe_render_pass.h"
#include "xe_layer.h"
#include "xe_core.h"

#include "xe_input.h"
#include "xe_scene.h"
#include "xe_utility.h"
#include "app_state.h"*/

static int WINDOW_WIDTH_SIZE = 1280;
static int WINDOW_HEIGHT_SIZE = 720;
static bool is_open = true;

int CALLBACK
WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR lp_cmd_line, int n_show_cmd)
{
#ifdef XE_DEBUG
    xe_platform::open_console();
#endif

    xe_config::ConfigData cd = {};

    const char* config_filename = "config.txt";
    FILE *config = fopen(config_filename, "r");
    
    char data[256];
    char output[512 * 512];
    
    if (config)
    {
        while (fgets(data, sizeof(data), config))
        {
            strcat(output, data);
        }

        fclose(config);
    }
   
    //parse_config_file(output, &cd);

    using namespace xe_graphics;

    xe_input::init();

    xe_platform::timer clock_time = {};
    xe_platform::start_timer(&clock_time);

    bool32 is_created = xe_platform::init_win32_platform(WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE);

    if (!is_created)
    {
        xe_utility::error("Failed to init window and context");
        xe_platform::shutdownApp();
    }

    xe_platform::win32_window_state& win_state = xe_platform::get_window_state();
    application::ApplicationState *current_app_state = application::getAppState();

    application::gameInit();

    using namespace xe_render;

    while (!win_state.is_closed)
    {
        xe_platform::update_platform();

        real32 current_time = xe_platform::time_elapsed(&clock_time);
        current_app_state->delta_time = current_time - current_app_state->last_frame;
        current_app_state->last_frame = current_time;

        xe_input::poll_events();

        application::gameUpdate(current_app_state->delta_time);

        application::gameSubmitRenderPasses(current_app_state->delta_time);

        ++current_app_state->frames_elapsed;

        if (xe_platform::time_elapsed(&clock_time) - current_app_state->start_time > 1.0f)
        {
            current_app_state->fps = current_app_state->frames_elapsed;
            current_app_state->frames_elapsed = 0;
            current_app_state->start_time += 1.0f;
        }

        printf("FPS: %d\n", current_app_state->fps);
    }

    xe_render::clear();
    xe_platform::destroy_platform_window();

    return (0);
}
