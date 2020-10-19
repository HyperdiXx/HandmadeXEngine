
#define WIN32_LEAN_AND_MEAN

#define WINDOW_NAME "XEngine"
#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

#include <windows.h>
#include <windowsx.h>
#include <xinput.h>
#include <objbase.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <audiopolicy.h>

#include "xengine\external\glcorearb.h"
#include "xengine\external\wglext.h"

#include "xengine\common.h"
#include "xengine\math.cpp"
#include "game\app_state.h"

#include "win32_platform.cpp"
#include "win32_file.cpp"
#include "win32_dll.cpp"
#include "win32_utility.cpp"
#include "win32_opengl.cpp"
#include "win32_wasapi.cpp"
#include "win32_daudio.cpp"
#include "win32_xinput.cpp"

#define DEBUG_LOG(data) printf(data)

global bool is_closed = false;
global PlatformState global_state = {};
global HDC global_device_context = {};
global HWND window_handle = {};

LRESULT CALLBACK win32_win_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

internal WNDCLASS create_win32window(HINSTANCE &h_instance)
{
    WNDCLASS window_class = {};
    window_class.hInstance = h_instance;
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = (WNDPROC)win32_win_proc;
    window_class.lpszClassName = "XEngine";
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hIcon = LoadIcon(NULL, IDI_WINLOGO);

    return window_class;
}

/*internal void printfLetter(char a)
{
    printf("%c, \n", a);
}

internal void 
parseFile()
{
    char *file_content = loadEntireFile("test.txt");

    while (*file_content != '\n')
    {
        token cur_token = get_parsed_token(file_content);

        ++file_content;
    }
}*/

internal void
Win32UpdateWindowRect()
{
    RECT client_rect = {};
    GetClientRect(window_handle, &client_rect);
    
    uint32 width = client_rect.right - client_rect.left;
    uint32 height = client_rect.bottom - client_rect.top;

    WindowOptions &options = global_state.options.window_options;

    if (options.window_width != width || options.window_height != height)
    {
        options.window_width = width;
        options.window_height = height;

        options.resized = true;
    }
}

int CALLBACK
WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR lp_cmd_line, int n_show_cmd)
{    
    // Load Game Code

    win32_game_code game_code = {};
    {
        if (!LoadGameCode(&game_code, "application.dll"))
        {
            DEBUG_LOG("Failed to load game code!\n");
        }
    }

    Win32SoundDevice win32_sound_dev = {};

    win32_sound_dev.channels = 2;
    win32_sound_dev.samples_per_second = 48000;
    win32_sound_dev.latency_frame_count = 48000;
    
    Win32LoadWASAPIDLL();
    Win32InitWASAPI(&win32_sound_dev);

    // Init function ptr

    platform_state = &global_state;

    global_state.LoadOpenGLProcedure = Win32LoadOpenglProcedure;
    global_state.AllocateMemory = Win32AllocVirtual;
    global_state.FreeMemory = Win32FreeVirtual;
    global_state.ReallocateMemory = Win32Realocate;
    global_state.render_api = PlatformState::RenderApi::OPENGL;

    WNDCLASS window_class = create_win32window(instance);
 
    if (!RegisterClass(&window_class))
    {
        DEBUG_LOG("Failed to register window!!!\n");
    }

    window_handle = CreateWindowEx(0, window_class.lpszClassName,
        "Engine", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        DEFAULT_WINDOW_WIDTH,
        DEFAULT_WINDOW_HEIGHT,
        0, 0, instance, 0);

    global_device_context = GetDC(window_handle);
    
    if (!Win32InitGraphicsDevice(&global_device_context, instance))
    {
        DEBUG_LOG("Failed to init OpenGL!");
    }

    ShowWindow(window_handle, n_show_cmd);

    game_code.LoadGameCode(platform_state);

    while (!is_closed)
    {
        MSG message = {};
        
        while (PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE) > 0)
        {
            if (message.message == WM_QUIT)
            {
                is_closed = true;
                return (0);
            }

            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        game_code.GameUpdate();
        SwapBuffers(global_device_context);
    }        

	return (0);
}


LRESULT CALLBACK
win32_win_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
{
    //if (ImGui_ImplWin32_WndProcHandler(window_handle, message, w_param, l_param))
    //    return true;

    LRESULT result = 0;
    //xe_platform::win32_window_state& win_state = xe_platform::get_window_state();

    switch (message)
    {
    case WM_CLOSE:
    {
        is_closed = true;
    } break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    } break;
    case WM_QUIT:
    {
        is_closed = true;
    } break;
    case WM_INPUT:
    {
        /*UINT size;

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
                //xe_utility::info("escape button pressed!");
                break;
            }
            default:
                break;
            }

        }
        else if (raw->header.dwType == RIM_TYPEMOUSE)
        {
            const RAWMOUSE& rawmouse = raw->data.mouse;

            xe_input::MouseState *mouse = xe_input::getMouseState();

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
                mouse->isLeftButtonPressed = true;

                POINT p;
                GetCursorPos(&p);
                if (ScreenToClient(window_handle, &p))
                {
                    mouse->position.x = p.x;
                    mouse->position.y = p.y;
                }

                xe_utility::info("left mouse button pressed!");
            }

            if (rawmouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_DOWN)
            {
                mouse->dtPosition.x = rawmouse.lLastX;
                mouse->dtPosition.y = rawmouse.lLastY;
                mouse->isRightButtonPressed = !mouse->isRightButtonPressed;
            }
        }
        return 0;*/
    } break;
    case WM_SIZE:
    {
        Win32UpdateWindowRect();

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
