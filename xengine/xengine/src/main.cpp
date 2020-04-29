
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

#ifdef GAPI_DX11
#include <thirdparty/imguit/imgui_impl_dx11.h>
#endif

#ifdef PLATFORM_WINDOWS
#include <thirdparty/imguit/imgui_impl_win32.h>
#include <thirdparty/imguit/imgui_impl_opengl3.h>
#endif

#include "xe_input.h"
#include "xe_scene.h"

#include "runtime/core/utility/log.h"

#include "app_state.h"

static int WINDOW_WIDTH_SIZE = 1280;
static int WINDOW_HEIGHT_SIZE = 720;

#define internal static

static bool is_open = true;

internal void 
win32_init_imgui_gl(HWND window)
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

#ifdef GAPI_DX11

internal void 
win32_init_imgui_dx11(HWND window, ID3D11Device *device, ID3D11DeviceContext *device_context)
{
    //IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(device, device_context);
}

#endif

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
        case WM_INPUT:
        {
            UINT size;

            GetRawInputData((HRAWINPUT)l_param, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));
            
            LPBYTE lpb = new BYTE[size];
            if (lpb == NULL)
            {
                return 0;
            }

            if (GetRawInputData((HRAWINPUT)l_param, RID_INPUT, lpb, &size, sizeof(RAWINPUTHEADER)) != size)
                OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));

            RAWINPUT* raw = (RAWINPUT*)lpb;

            if (raw->header.dwType == RIM_TYPEKEYBOARD)
            {
                const RAWKEYBOARD& rawkeyboard = raw->data.keyboard;

                switch (rawkeyboard.VKey)
                {
                case VK_ESCAPE:
                {
                    xe_utility::info("escape button pressed!");  
                    break;
                }
                default:
                    break;
                }

            }
            else if (raw->header.dwType == RIM_TYPEMOUSE)
            {
                const RAWMOUSE& rawmouse = raw->data.mouse;
                    
                xe_input::mouse_state *mouse = xe_input::get_mouse_state();

                mouse->is_left_button_pressed = false;
                
                if (raw->data.mouse.usFlags == MOUSE_MOVE_RELATIVE)
                {
                    mouse->position.x = rawmouse.lLastX;
                    mouse->position.y = rawmouse.lLastY;
                    
                    if (rawmouse.usButtonFlags == RI_MOUSE_WHEEL)
                    {
                        mouse->wheel += float((SHORT)rawmouse.usButtonData) / float(WHEEL_DELTA);
                    }
                }
                else if (raw->data.mouse.usFlags == MOUSE_MOVE_ABSOLUTE)
                {
                    mouse->position.x += rawmouse.lLastX;
                    mouse->position.y += rawmouse.lLastY;
                }

                if (rawmouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_DOWN)
                {
                    mouse->is_left_button_pressed = true;
                    xe_utility::info("left mouse button pressed!");
                }
                
                if (rawmouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_DOWN)
                {
                    mouse->dt_position.x = rawmouse.lLastX;
                    mouse->dt_position.y = rawmouse.lLastY;
                    mouse->is_right_button_pressed = !mouse->is_right_button_pressed;
                }
            }
            return 0;
        } break;
        case WM_SIZE:
        {
            WINDOW_WIDTH_SIZE = LOWORD(l_param);
            WINDOW_HEIGHT_SIZE = HIWORD(l_param);
            
            xe_graphics::graphics_device *device = xe_render::get_device();
            if (device)
            {
                device->set_viewport(0, 0, WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE);
                xe_graphics::viewport &vp_state = device->get_viewport();
                vp_state.width = WINDOW_WIDTH_SIZE;
                vp_state.height = WINDOW_HEIGHT_SIZE;
            }
                
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
            
            xe_input::init();

            xe_platform::timer clock_time = {};
            xe_platform::start_timer(&clock_time);
            
            static real32 delta_time;
            static real32 last_frame = 0.0f;
            static real32 start_time = 0;
            static uint32 frames_elapsed = 0;
            static uint32 fps = 0;

#ifdef GAPI_GL

            graphics_device *device = new graphics_device_gl(window_handle);
            xe_render::set_device(device);
            
            win32_init_gl_loader();
            win32_init_imgui_gl(window_handle);            
            xe_render::init_render_gl();
            
            application::load_state();

            xe_scene::scene new_scene = xe_scene::create_scene("TestScene");
            xe_scene::scene pbr_scene = xe_scene::create_scene("PBRScene");

            xe_scene::load_test_scene(&new_scene);
            xe_scene::load_spheres_scene(&pbr_scene);

            application::application_state *current_app_state = application::get_app_state();
            application::set_active_scene(&pbr_scene);

            ImGuiIO &io = ImGui::GetIO();

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
            graphics_device *device = new graphics_device_dx11(window_handle);
            set_device(device);
           // win32_init_imgui_dx11(window_handle, );

            init_render_dx11();
#endif
       
            //------------------------------------------------------------//

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

                real32 current_time = xe_platform::time_elapsed(&clock_time);
                delta_time = current_time - last_frame;
                last_frame = current_time;
                
                xe_input::poll_events();
               
                application::game_update(delta_time);

                device->start_execution();

                //shadow_pass.render();

                //viewport vp_state = device->get_viewport();
                //device->set_viewport(0, 0, vp_state.width, vp_state.height);
                //device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          
                //shadow_pass.bind_depth_texture();
                
                /*main_render_pass->update(io.DeltaTime);
                main_render_pass->render();
                
                texture2D pass_texture = main_render_pass->get_color_texture();

                gamma_correction.set_color_texture(&pass_texture);
                gamma_correction.render();*/

                pbr_setup.update(io.DeltaTime);
                pbr_setup.render();

                render_pass_2D->update(io.DeltaTime);
                render_pass_2D->render();
               
                win32_imgui_new_frame();                
                top_bar(); 

                win32_imgui_post_update();

                device->check_error();

                device->end_execution();

                ++frames_elapsed;

                if (xe_platform::time_elapsed(&clock_time) - start_time > 1.0f)
                {
                    fps = frames_elapsed;
                    frames_elapsed = 0;
                    start_time += 1.0f;
                }

            }
        }

        xe_render::clear();

        win32_imgui_shutdown();
        wglMakeCurrent(0, 0);

        DestroyWindow(window_handle);
    }
   
    return (0);
}
