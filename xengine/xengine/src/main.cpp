
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
#include "config.h"
#include "xe_render.h"
#include "xe_render_pass.h"
#include "xe_core.h"

#ifdef GAPI_GL
#include "xe_graphics_device_gl.h"
#endif 

#ifdef GAPI_DX11
#include "xe_graphics_device_dx11.h"
#endif

#include "png.h"

// ImGui
#include <thirdparty/imguit/imgui.h>

#ifdef GAPI_GL
#include <thirdparty/imguit/imgui_impl_opengl3.h>
#endif 

#ifdef PLATFORM_WINDOWS
#include <thirdparty/imguit/imgui_impl_win32.h>
#endif

#include "xe_input.h"
#include "xe_scene.h"

#include "runtime/core/utility/log.h"

#include "app_state.h"

static int WINDOW_WIDTH_SIZE = 1280;
static int WINDOW_HEIGHT_SIZE = 720;

#define internal static

static bool is_open = true;

static void 
win32_init_imgui(HWND window)
{
    //IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

    const char* glsl_version = "#version 330";
    ImGui_ImplWin32_Init(window);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

internal void 
win32_imgui_new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

internal void
win32_imgui_shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

internal void
win32_imgui_post_update()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

internal void 
top_bar()
{
    bool show_log = true;
    bool *open = &show_log;
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O", false))
            {
                printf("Pressed on menu bar!\n");

                int a = 312;
                int b = a * 5;
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Animation"))
        {
            if (ImGui::MenuItem("AnimTree", NULL, false))
            {
                xe_utility::info("Pressed on animation tree window");
                ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
                ImGui::Begin("Example: Log", open);
                ImGui::End();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Options"))
        {
            if (ImGui::MenuItem("Help", NULL, false))
                printf("Pressed on help window\n");
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

internal void
swap_bytes(uint32* bytes)
{     
    uint32 s = (*bytes);

    *bytes = ((s << 24) | ((s & 0xFF00) << 8) | ((s >> 8) & 0xFF00) | (s >> 24));
}

#define CONSUME(File, type) (type*)consume_size(File, sizeof(type))

internal void* 
consume_size(xe_core::file *file, uint32 size)
{
    void* res = 0;

    if (file->size >= size)
    {
        res = file->data;
        file->data = (uint32*)file->data + size;
        file->size -= size;
    }
    else
    {
        file->size = 0;
    }

    return res;
}

internal void
parse_png(xe_core::file f)
{
    printf("PNG size: %d\n" , f.size);

    xe_core::file *read = &f;

    png_head *pngheader = CONSUME(read, png_head);

    if (pngheader)
    {
        while (read->size > 0)
        {
            png_chunk *png_chunk_head = CONSUME(read, png_chunk);
            if (png_chunk_head)
            {
                swap_bytes(&png_chunk_head->size);

                switch (png_chunk_head->typeuint)
                {
                case FOURCC("IHDR"):
                {
                    printf("IHDR\n");
                } break;
                case FOURCC("IDAT"):
                {
                    printf("IDAT\n");
                } break;
                }

                void *png_chynk_data = consume_size(read, png_chunk_head->size);
                png_footer *png_chunk_footer = CONSUME(read, png_footer);
                swap_bytes(&png_chunk_footer->CRC);
            }
        }
    }

    int a = 21;

}

internal 
void start_png_parser()
{
#if 0
    if (arg_count < 2)
    {
        printf("Error: specify file name .png\n");
        return 1;
    }
#endif
    const char* read_filename = "engineassets/get.png";

    fprintf(stdout, "Loading PNG %s...\n", read_filename);

    xe_core::file png_image = xe_core::read_whole_file(read_filename);

    parse_png(png_image);
}

internal void
win32_init_gl(HWND window_handle)
{
    HDC window_dc = GetDC(window_handle);

    PIXELFORMATDESCRIPTOR pixel_format_descriptor = {};
    memset(&pixel_format_descriptor, 0, sizeof(pixel_format_descriptor));
    pixel_format_descriptor.nSize = sizeof(pixel_format_descriptor);
    pixel_format_descriptor.nVersion = 1;
    pixel_format_descriptor.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pixel_format_descriptor.cColorBits = 32;
    pixel_format_descriptor.cRedBits = 8;
    pixel_format_descriptor.cGreenBits = 8;
    pixel_format_descriptor.cBlueBits = 8;
    pixel_format_descriptor.cAlphaBits = 8;
    pixel_format_descriptor.cDepthBits = 24;
    pixel_format_descriptor.iLayerType = PFD_MAIN_PLANE;

    int pixel_format_index = ChoosePixelFormat(window_dc, &pixel_format_descriptor);
    PIXELFORMATDESCRIPTOR sug_pixel_format;
    DescribePixelFormat(window_dc, pixel_format_index, sizeof(sug_pixel_format), &sug_pixel_format);
    SetPixelFormat(window_dc, pixel_format_index, &sug_pixel_format);

    HGLRC gl_render_context = wglCreateContext(window_dc);
    if (!wglMakeCurrent(window_dc, gl_render_context))
    {
        printf("Failed to init GLCOntext");
    }

    ReleaseDC(window_handle, window_dc);
}

internal
void win32_init_gl_loader()
{
    if (!gladLoadGL())
        printf("Failed to init OpenGL loader!\n");

    const char *gl_vendor = (char*)glGetString(GL_VENDOR);
    const char *gl_renderer = (char*)glGetString(GL_RENDERER);
    const char *gl_version = (char*)glGetString(GL_VERSION);

    xe_utility::info(gl_vendor);
    xe_utility::info(gl_renderer);
    xe_utility::info(gl_version);
}

internal 
void update()
{

}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
internal LRESULT CALLBACK
win32_win_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
{
    if (ImGui_ImplWin32_WndProcHandler(window_handle, message, w_param, l_param))
        return true;

    LRESULT result = 0;

    switch(message)
    {
        case WM_CLOSE:
        {
            is_open = false;
        } break;
        case WM_DESTROY:
        {
            is_open = false;
        } break;
        case WM_QUIT:
        {
            is_open = false;
        } break;
        case WM_SIZE:
        {
            WINDOW_WIDTH_SIZE = LOWORD(l_param);
            WINDOW_HEIGHT_SIZE = HIWORD(l_param);
            
            xe_graphics::graphics_device *device = xe_render::get_device();
            if(device != nullptr)
                device->set_viewport(0, 0, WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE);
            
            OutputDebugStringA("Resizing window\n");
        } break;
        case WM_ACTIVATEAPP:
        {

        } break;
        default:
        {
            result = DefWindowProc(window_handle, message, w_param, l_param);
        } break;
    }
  
    return result;
}

void set_pos(int posX, int posY)
{
    int startX = posX;
    int startY = posX;
}

struct config_data
{
    const char *name;
    bool32 windowed;
};

internal void
parse_config_file(const char *data, config_data *cd)
{
    char data_string[128];
    strcpy(data_string, data);

    while (data_string != "\n")
    {
        char *split_name = strtok(data_string, ":");
        char *result_value = strtok(NULL, "\n");

        if (strcmp(split_name, "name") == 0)
        {
            cd->name = result_value;
        }
        else if (strcmp(split_name, "windowed") == 0)
        {
            if (strcmp(result_value, "true") == 0)
                cd->windowed = true;
            else
                cd->windowed = false;
        }
    }
}


#define DEBUG

int CALLBACK
WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR lp_cmd_line, int n_show_cmd)
{ 

#ifdef DEBUG

    AllocConsole();
    SetConsoleTitle("Dev console");

    FILE *out_f;
    freopen_s(&out_f, "CONOUT$", "w", stdout);
    freopen_s(&out_f, "CONIN$", "w", stdin);
    freopen_s(&out_f, "CONERR$", "w", stderr);
#endif

    config_data cd = {};

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

    WNDCLASS window = {};

    window.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    window.lpfnWndProc = win32_win_proc;
    window.hInstance = instance;
    window.lpszClassName = "Engine";

    if (RegisterClass(&window))
    {
        HWND& window_handle = xe_platform::get_window_handle();

        window_handle = CreateWindowEx(0, window.lpszClassName,
                                            "Engine", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                            CW_USEDEFAULT, CW_USEDEFAULT,
                                            WINDOW_WIDTH_SIZE,
                                            WINDOW_HEIGHT_SIZE,
                                            0, 0, instance, 0);

        if (window_handle)
        {
            using namespace xe_graphics;
            using namespace xe_render;
            
            xe_input::init();

#ifdef GAPI_GL

            graphics_device *device = new graphics_device_gl(window_handle);
            set_device(device);
            win32_init_gl_loader();
            win32_init_imgui(window_handle);
            
            init_render_gl();

#endif 

#ifdef GAPI_DX11
            graphics_device *device = new graphics_device_dx11(window_handle);
            set_device(device);

            init_render_dx11();
#endif
            ImGuiIO &io = ImGui::GetIO();

            application::application_state app_state = {};
            application::load_state(&app_state);

            xe_scene::scene new_scene = xe_scene::create_scene("TestScene");

            xe_ecs::entity* test_entity = application::get_entity(&app_state);
            test_entity->set_entity_type(xe_ecs::ENTITY_TYPE::ENT_STATIC_OBJECT);

            xe_ecs::entity* light_entity = application::get_entity(&app_state);
            light_entity->set_entity_type(xe_ecs::ENTITY_TYPE::ENT_STATIC_OBJECT);

            xe_ecs::entity* plane_entity = application::get_entity(&app_state);
            plane_entity->set_entity_type(xe_ecs::ENTITY_TYPE::ENT_STATIC_OBJECT);
     
            assert(test_entity != nullptr);
            assert(light_entity != nullptr);
            assert(plane_entity != nullptr);

            xe_ecs::mesh_component *character_mesh = new xe_ecs::mesh_component();
            character_mesh->model_asset = &app_state.assets_3D.models3D["Nano"];
           
            xe_ecs::transform_component *nano_transform = new xe_ecs::transform_component();
            nano_transform->set_translation(-20.0f, -9.0f, -50.0f);
        
            test_entity->add_component(character_mesh);
            test_entity->add_component(nano_transform);            

            for (int i = 0; i < 10; ++i)
            {
                xe_ecs::entity* ent = application::get_entity(&app_state);
                ent->set_entity_type(xe_ecs::ENTITY_TYPE::ENT_STATIC_OBJECT);

                xe_ecs::transform_component *transform = new xe_ecs::transform_component(); 
                transform->set_translation(30.0f * (i - 5), 0.0f, -5.0f * (i + 1));
                transform->set_scale(0.2f, 0.2f, 0.2f);

                xe_ecs::mesh_component *loading_model = new xe_ecs::mesh_component();
                loading_model->model_asset = &app_state.assets_3D.models3D["Cube"];;
                loading_model->draw_with_color = true;

                ent->add_component(transform);
                ent->add_component(loading_model);
                
                new_scene.entities.push_back(ent);
            }

            xe_ecs::mesh_component *cube_mesh = new xe_ecs::mesh_component();
            cube_mesh->model_asset = &app_state.assets_3D.models3D["Cube"];
            cube_mesh->draw_with_color = true;

            xe_ecs::dir_light *dl = new xe_ecs::dir_light();
            dl->color = glm::vec3(0.8f, 0.7f, 0.8f);
            dl->entensity = 0.9f;

            xe_ecs::transform_component *light_transform = new xe_ecs::transform_component();
            light_transform->set_translation(0.0f, 20.0f, -5.0f);
            light_transform->set_scale(0.2f, 0.2f, 0.2f);

            light_entity->add_component(dl);
            light_entity->add_component(light_transform);
            light_entity->add_component(cube_mesh);

            xe_ecs::mesh_component *plane_mesh = new xe_ecs::mesh_component();
            plane_mesh->model_asset = &app_state.assets_3D.models3D["Cube"];
            plane_mesh->draw_with_color = true;

            xe_ecs::transform_component *transform_plane = new xe_ecs::transform_component();

            transform_plane->set_translation(3.0f, -10.0f, 75.0f);
            transform_plane->set_scale(10.0f, 0.001f, 10.0f);

            plane_entity->add_component(plane_mesh);
            plane_entity->add_component(transform_plane);

            new_scene.entities.push_back(test_entity);
            new_scene.entities.push_back(light_entity);
            new_scene.entities.push_back(plane_entity);

            app_state.active_scene = new_scene;

            //------------------------------------------------------------//

            render_pass *render_pass_2D = new render_pass2D();
            set_render_pass(render_pass_2D);

            render_pass_2D->init();

            render_pass3D *main_render_pass = new render_pass3D();
            main_render_pass->init();
            main_render_pass->set_scene(&app_state.active_scene);

            gamma_correction_pass gamma_correction = {};
            gamma_correction.init();

            shadow_map_pass shadow_pass = {};
            shadow_pass.init();
            shadow_pass.set_scene(&app_state.active_scene);

            device->clear_color(0.1f, 0.1f, 0.1f, 1.0f);
  
            using namespace xe_render;

            while (is_open)
            {
                MSG message = {};
                while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
                
                xe_input::poll_events();
               
                device->start_execution();

                //shadow_pass.render();

                viewport vp_state = device->get_viewport();

                device->set_viewport(0, 0, vp_state.width, vp_state.height);
                device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //shadow_pass.bind_depth_texture();

                main_render_pass->update(io.DeltaTime);
                main_render_pass->render();
                
                texture2D pass_texture = main_render_pass->get_color_texture();

                gamma_correction.set_color_texture(&pass_texture);
                gamma_correction.render();

                render_pass_2D->update(io.DeltaTime);
                render_pass_2D->render();

                win32_imgui_new_frame();                
                top_bar();                            
                win32_imgui_post_update();

                device->check_error();

                device->end_execution();
            }
        }

        win32_imgui_shutdown();
        wglMakeCurrent(0, 0);

        DestroyWindow(window_handle);
    }
   
    return (0);
}
