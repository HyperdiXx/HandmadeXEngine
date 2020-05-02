#include "xe_gui.h"

#include "xe_platform.h"
#include "xe_render.h"
#include "xe_utility.h"

// ImGui
#include <thirdparty/imguit/imgui.h>

#ifdef GAPI_GL
#include <thirdparty/imguit/imgui_impl_opengl3.h>
#endif 

#ifdef GAPI_DX11
#include <thirdparty/imguit/imgui_impl_dx11.h>
#include "xe_graphics_device_dx11.h"
#endif

#ifdef PLATFORM_WINDOWS
#include <thirdparty/imguit/imgui_impl_win32.h>
#endif

namespace xe_gui
{
    void draw_top_bar()
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

    void clear_context()
    {
#ifdef GAPI_GL
        ImGui_ImplOpenGL3_Shutdown();
#endif 

#ifdef GAPI_DX11
        ImGui_ImplDX11_Shutdown();
#endif // GAPI_DX11

        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }

    void init_imgui_impl()
    {
        xe_graphics::graphics_device *device = xe_render::get_device();
        HWND &wnd_handle = xe_platform::get_window_handle();
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

        const char* glsl_version = "#version 330";
        ImGui_ImplWin32_Init(wnd_handle);
        
#ifdef GAPI_GL
        ImGui_ImplOpenGL3_Init(glsl_version);
#endif 

#ifdef GAPI_DX11        

        ImGui_ImplDX11_Init(xe_graphics::graphics_device_dx11::get_api_device(), xe_graphics::graphics_device_dx11::get_api_device_context());
#endif 
    }

    void start_frame()
    {
        xe_graphics::graphics_device *device = xe_render::get_device();
#ifdef GAPI_GL
        ImGui_ImplOpenGL3_NewFrame();
#endif // GAPI_GL

#ifdef GAPI_DX11
        ImGui_ImplDX11_NewFrame();
#endif
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }

    void end_frame()
    {
        ImGui::Render();

#ifdef GAPI_GL
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

#ifdef GAPI_DX11
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
    }
}
