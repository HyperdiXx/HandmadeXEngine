
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




#include "xe_platform.h"
#include <math/xemath.h>
#include "config.h"
#include "xe_render.h"
#include "xe_core.h"
#include "xe_graphics_device_gl.h"
#include "png.h"

// ImGui
#include <thirdparty/imguit/imgui.h>
#include <thirdparty/imguit/imgui_impl_opengl3.h>
#include <thirdparty/imguit/imgui_impl_win32.h>



#define internal static

static bool is_open = true;

static void 
win32_init_imgui(HWND window)
{
    glEnable(GL_DEPTH_TEST);
    IMGUI_CHECKVERSION();
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
win32_ingui_post_update()
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
                //Log::info("Pressed on animation tree window");
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

#ifdef DEBUG
int main()
{
    using namespace XEngine;

    TestApp testapp;

    testapp.run();

    return (0);
}
#endif

internal void
win32_init_gl(HWND window_handle, HINSTANCE h_instance)
{
    HDC window_dc = GetDC(window_handle);

    PIXELFORMATDESCRIPTOR pixel_format_descriptor = {};
    pixel_format_descriptor.nSize = sizeof(pixel_format_descriptor);
    pixel_format_descriptor.nVersion = 1;
    pixel_format_descriptor.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pixel_format_descriptor.cColorBits = 32;
    pixel_format_descriptor.cAlphaBits = 8;
    pixel_format_descriptor.iLayerType = PFD_MAIN_PLANE;

    int pixel_format_index = ChoosePixelFormat(window_dc, &pixel_format_descriptor);
    PIXELFORMATDESCRIPTOR sug_pixel_format;
    DescribePixelFormat(window_dc, pixel_format_index, sizeof(sug_pixel_format), &sug_pixel_format);
    SetPixelFormat(window_dc, pixel_format_index, &sug_pixel_format);

    HGLRC gl_render_context = wglCreateContext(window_dc);
    if (wglMakeCurrent(window_dc, gl_render_context))
    {

    }

    ReleaseDC(window_handle, window_dc);
}

internal
void win32_init_gl_loader()
{
    if (!gladLoadGL())
        printf("Failed to init OpenGL loader!\n");
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

int CALLBACK
WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR lp_cmd_line, int n_show_cmd)
{ 
    WNDCLASS window = {};

    window.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    window.lpfnWndProc = win32_win_proc;
    window.hInstance = instance;
    window.lpszClassName = "Engine";

    if (RegisterClass(&window))
    {
        HWND window_handle = xe_platform::get_window_handle();

        window_handle = CreateWindowEx(0, window.lpszClassName,
                                            "Engine", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                            CW_USEDEFAULT, CW_USEDEFAULT,
                                            WINDOWS_WIDTH,
                                            WINDOWS_HEIGHT,
                                            0, 0, instance, 0);

        if (window_handle)
        {
            HDC dc = GetDC(window_handle);

            using namespace xe_graphics;
            using namespace xe_render;
            
            graphics_device *device = new graphics_device_gl(window_handle, false);
            set_device(device);

            win32_init_gl_loader();
            win32_init_imgui(window_handle);
           
            texture2D diff_texture;
           
            init_render();

            quad quad_test = {};

            create_quad(&quad_test);

            device->create_texture2D("engineassets/get.png", &diff_texture);            

            shader *simple_shader = get_simple_shader();
            shader *model_shader = get_model_shader();

            device->bind_shader(simple_shader);
            
            //triangle_shader->setInt("textureDiffuse", 0);

            device->bind_shader(model_shader);

            //model_shader->setInt("tex_diff", 0);

            while (is_open)
            {
                MSG message = {};
                while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }

                device->clear_color(0.9f, 0.9f, 0.9f, 1.0f);
                device->clear(GL_COLOR_BUFFER_BIT);

                win32_imgui_new_frame();
                
                top_bar();

                //ImGui::ShowDemoWindow();

                win32_ingui_post_update();

                SwapBuffers(dc);
            }
        }
    }

    win32_imgui_shutdown();

    return (0);
}
