
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
#include "xe_platform.h"
#include <math/xemath.h>
#include "xe_config.h"
#include "xe_render_pass.h"
#include "xe_core.h"

#include "xe_input.h"
#include "xe_scene.h"
#include "xe_utility.h"
#include "app_state.h"

#include "xe_gui.h"

static int WINDOW_WIDTH_SIZE = 1280;
static int WINDOW_HEIGHT_SIZE = 720;
static bool is_open = true;

#define DEBUG

int CALLBACK
WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR lp_cmd_line, int n_show_cmd)
{ 
#ifdef DEBUG
    xe_platform::open_console();
#endif

    xe_config::config_data cd = {};

    const char* config_filename = "config.txt";
    FILE *config = fopen(config_filename, "r");

    char data[256];
    char output[512 * 512];

    while (fgets(data, sizeof(data), config))
    {        
        strcat(output, data);
    }
        
    fclose(config);

    //parse_config_file(output, &cd);

    using namespace xe_graphics;

    xe_input::init();

    xe_platform::timer clock_time = {};
    xe_platform::start_timer(&clock_time);

    bool32 is_created = xe_platform::init_win32_platform(WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE);

    if (!is_created)
    {
        xe_utility::error("Failed to init window and context");
        exit(0);
    }

    xe_platform::win32_window_state& win_state = xe_platform::get_window_state();
    application::application_state *current_app_state = application::get_app_state();

#ifdef GAPI_GL

    application::load_state();

    xe_scene::scene new_scene = xe_scene::create_scene("TestScene");
    xe_scene::scene pbr_scene = xe_scene::create_scene("PBRScene");

    xe_scene::load_test_scene(&new_scene);
    xe_scene::load_spheres_scene(&pbr_scene);
    application::set_active_scene(&new_scene);

    render_pass *render_pass_2D = new render_pass2D();
    render_pass_2D->init();

    xe_render::set_render_pass(render_pass_2D);

    render_pass3D *main_render_pass = new render_pass3D();
    main_render_pass->init();
    main_render_pass->set_scene(&current_app_state->active_scene);

    gamma_correction_pass gamma_correction = {};
    gamma_correction.init();

    shadow_map_pass shadow_pass = {};
    shadow_pass.init();
    shadow_pass.set_scene(&current_app_state->active_scene);

    pbr_pass pbr_setup = {};
    pbr_setup.init();

    pbr_scene.passes.push_back(&pbr_setup);

#endif 

#ifdef GAPI_DX11
    

#endif

    //------------------------------------------------------------//
   
    graphics_device *device = xe_render::get_device();
    device->clear_color(0.1f, 0.1f, 0.1f, 1.0f);

    using namespace xe_render;

    while (!win_state.is_closed)
    {
        xe_platform::update_platform();

        real32 current_time = xe_platform::time_elapsed(&clock_time);
        current_app_state->delta_time = current_time - current_app_state->last_frame;
        current_app_state->last_frame = current_time;

        xe_input::poll_events();

        application::game_update(current_app_state->delta_time);

        device->start_execution();

        //shadow_pass.render();

        //viewport vp_state = device->get_viewport();
        //device->set_viewport(0, 0, vp_state.width, vp_state.height);
        //device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //shadow_pass.bind_depth_texture();

        //main_render_pass->update(current_app_state->delta_time);
        //main_render_pass->render();

        //texture2D pass_texture = main_render_pass->get_color_texture();

        //gamma_correction.set_color_texture(&pass_texture);
        //gamma_correction.render();

        //pbr_setup.update(current_app_state->delta_time);
        //pbr_setup.render();

        //render_pass_2D->update(current_app_state->delta_time);
        //render_pass_2D->render();

        xe_gui::start_frame();
        xe_gui::draw_top_bar();
        xe_gui::end_frame();

        device->check_error();

        device->end_execution();

        ++current_app_state->frames_elapsed;

        if (xe_platform::time_elapsed(&clock_time) - current_app_state->start_time > 1.0f)
        {
            current_app_state->fps = current_app_state->frames_elapsed;
            current_app_state->frames_elapsed = 0;
            current_app_state->start_time += 1.0f;
        }
    }

    xe_render::clear();
    xe_platform::destroy_platform_window();
 
    return (0);
}
