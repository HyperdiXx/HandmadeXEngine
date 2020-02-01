
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
#include <glad/glad.h>

#include <math/xemath.h>

#include "png.h"

#define internal static
#define global static

global int DEFAULT_WINDOW_WIDTH = 1280;
global int DEFAULT_WINDOW_HEIGHT = 720;

global bool is_open = true;

struct file
{
    uint32 size;
    void *data;
};

file read_whole_file(const char *filename)
{
    file res = {};

    FILE *op = fopen(filename, "rb");

    if (op)
    {
        fseek(op, 0, SEEK_END);
        res.size = ftell(op);
        fseek(op, 0, SEEK_SET);

        res.data = malloc(res.size);
        fread(res.data, res.size, 1, op);
        fclose(op);
    }
    else
    {
        printf("ERROR: Cant open file %s!\n", filename);
    }

    return res;
}

internal void
swap_bytes(uint32* bytes)
{     
    uint32 s = (*bytes);

    *bytes = ((s << 24) | ((s & 0xFF00) << 8) | ((s >> 8) & 0xFF00) | (s >> 24));
}

#define CONSUME(File, type) (type*)consume_size(File, sizeof(type))

internal void* 
consume_size(file *file, uint32 size)
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
parse_png(file f)
{
    printf("PNG size: %d\n" , f.size);

    file *read = &f;

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

    file png_image = read_whole_file(read_filename);

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

internal LRESULT CALLBACK
win32_win_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
{
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
        HWND window_handle = CreateWindowEx(0, window.lpszClassName,
                                            "Engine", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                            CW_USEDEFAULT, CW_USEDEFAULT,
                                            DEFAULT_WINDOW_WIDTH,
                                            DEFAULT_WINDOW_HEIGHT,
                                            0, 0, instance, 0);

        if (window_handle)
        {
            HDC dc = GetDC(window_handle);
            win32_init_gl(window_handle, instance);
            win32_init_gl_loader();


            while (is_open)
            {
                MSG message = {};
                while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }

                glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                update();

                SwapBuffers(dc);
            }
        }
    }

    return (0);
}
