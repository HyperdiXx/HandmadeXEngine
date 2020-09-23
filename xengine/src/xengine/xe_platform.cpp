#include "xe_platform.h"
#include "xe_render.h"

#ifdef GAPI_GL
#include "xe_graphics_device_gl.h"
#endif 

#ifdef GAPI_DX11
#include "xe_graphics_device_dx11.h"
#endif

#include "xe_input.h"
#include "xe_utility.h"

#ifdef PLATFORM_WINDOWS

LRESULT CALLBACK win32_win_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

WNDCLASS xe_platform::create_platform_win32window()
{
    WNDCLASS window_class = {};
    window_class.hInstance = get_hInstance();
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = (WNDPROC)win32_win_proc;
    window_class.lpszClassName = "XEngine";
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hIcon = LoadIcon(NULL, IDI_WINLOGO);

    return window_class;
}

void xe_platform::open_console()
{
    AllocConsole();
    SetConsoleTitle("Dev console");

    FILE *out_f;
    freopen_s(&out_f, "CONOUT$", "w", stdout);
    freopen_s(&out_f, "CONIN$", "w", stdin);
    freopen_s(&out_f, "CONERR$", "w", stderr);
}

void xe_platform::update_platform()
{
    MSG message;
    while (PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE) > 0)
    {
        if (message.message == WM_QUIT)
        {
            win32_window_state& win_state = get_window_state();
            win_state.is_closed = true;
            return;
        }
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    // input update...
}

bool32 xe_platform::init_win32_platform(uint32 window_w, uint32 window_h)
{
    HINSTANCE &hInstance = get_hInstance();

    WNDCLASS window = create_platform_win32window();

    if (!RegisterClass(&window))
    {
        xe_utility::error("Failed to register win32 window class!");
        return false;
    }

    HWND& window_handle = xe_platform::get_window_handle();

    window_handle = CreateWindowEx(0, window.lpszClassName,
                    "Engine", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                    CW_USEDEFAULT, CW_USEDEFAULT,
                    window_w,
                    window_h,
                    0, 0, hInstance, 0);
    
    if (!window_handle)    
    {
        xe_utility::error("Failed to create win32 window class!");
        return false;
    }

    using namespace xe_graphics;

#ifdef GAPI_GL

    GraphicsDevice *device = new GraphicsDeviceGL(window_handle);
    xe_render::setDevice(device);

    device->loadBindings();
    xe_render::initGui();
    xe_render::initRenderGL();

#endif // 

#ifdef GAPI_DX11
    graphics_device *device = new graphics_device_dx11(window_handle);
    xe_render::set_device(device);

    device->load_bindings();
    xe_render::init_gui();

    xe_render::init_render_dx11();
#endif

    return true;
}

void xe_platform::destroy_platform_window()
{
#ifdef GAPI_GL
    
#endif // DEBUG

    DestroyWindow(get_window_handle());
}

void xe_platform::start_timer(timer *time)
{
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time->start);
    time->frequ = 1.0f / frequency.QuadPart;
}

void xe_platform::reset_timer(timer *time)
{
    QueryPerformanceCounter(&time->start);
}

real32 xe_platform::time_elapsed(timer *time)
{
    LARGE_INTEGER cur;
    QueryPerformanceCounter(&cur);
    unsigned __int64 timeElapsed = cur.QuadPart - time->start.QuadPart;
    return (real32)(timeElapsed * time->frequ);
}

LARGE_INTEGER xe_platform::get_wall_clock()
{
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);
    return (end);
}

bool32 xe_platform::load_DLL(const char *name)
{
    HMODULE library = LoadLibrary(name);
    
    if (!library)
    {
        return false;
    }

    return true;
}

void xe_platform::shutdownApp()
{
    exit(0);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK
win32_win_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
{
    if (ImGui_ImplWin32_WndProcHandler(window_handle, message, w_param, l_param))
        return true;

    LRESULT result = 0;
    xe_platform::win32_window_state& win_state = xe_platform::get_window_state();

    switch (message)
    {
    case WM_CLOSE:
    {
        win_state.is_closed = true;
    } break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    } break;
    case WM_QUIT:
    {
        win_state.is_closed = true; 
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
        return 0;
    } break;
    case WM_SIZE:
    {
        /*WINDOW_WIDTH_SIZE = LOWORD(l_param);
        WINDOW_HEIGHT_SIZE = HIWORD(l_param);

        xe_graphics::graphics_device *device = xe_render::get_device();
        if (device)
        {
            device->set_viewport(0, 0, WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE);
            xe_graphics::viewport &vp_state = device->get_viewport();
            vp_state.width = WINDOW_WIDTH_SIZE;
            vp_state.height = WINDOW_HEIGHT_SIZE;
        }*/

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


#endif // PLATFORM_WINDOWS

