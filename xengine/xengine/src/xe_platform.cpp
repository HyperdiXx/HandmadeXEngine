#include "xe_platform.h"

#ifdef PLATFORM_WINDOWS

LRESULT CALLBACK win32_win_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void xe_platform::create_platform_win32window()
{
    WNDCLASS winClass = {};
    winClass.hInstance = get_hInstance();
    winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    winClass.lpfnWndProc = (WNDPROC)win32_win_proc;
    winClass.lpszClassName = "XEngine";
    winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
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

bool32 xe_platform::load_library(const char *name)
{
    HMODULE library = LoadLibrary(name);
    if (library)
        return false;
    return true;
}

LRESULT CALLBACK
win32_win_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
{
    LRESULT result = 0;

    switch (message)
    {
    case WM_CLOSE:
    {
        //is_open = false;
    } break;
    case WM_DESTROY:
    {
        //is_open = false;
    } break;
    case WM_QUIT:
    {
        //is_open = false;
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

            /*xe_input::mouse_state *mouse = xe_input::get_mouse_state();

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
            }*/
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

