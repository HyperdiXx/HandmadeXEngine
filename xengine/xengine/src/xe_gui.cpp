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
    static ElementHolder gui = {};

    void drawTopBar()
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

    void drawButton(const char *wo)
    {
        ImGui::Begin("Test");

        ImGui::Text(wo);

        ImGui::End();
    }

    void clearContext()
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

    void drawUI()
    {
        if (gui.uiStates.size() == 0)
            return;

        using namespace xe_render;
        using namespace xe_graphics;
        for (uint32 i = 0; i < gui.uiStates.size(); ++i)
        {
            UIElement &element = gui.uiStates[i];
            switch (element.type)
            {
            case UI_BUTTON:
            {   
                Quad q = {};

                q.x = element.x;
                q.y = element.y;
                q.w = element.width;
                q.h = element.height;
                
                Shader *color = getShader("simple_pos");
                if (color)
                {
                    drawQuad(&q, color, nullptr);
                }
            } break;               
            case UI_WIDGET:
            {

            } break;            
            default:
                break;
            }

        }
    }

    bool makeButton(uint64 id, real32 x, real32 y, real32 w, real32 h, const char *text)
    {
        UIElement *elem = NULL;

        for (uint32_t i = 0; i < gui.uiStates.size(); ++i)
        {
            if (gui.uiStates[i].id == id)
            {
                elem = &gui.uiStates[i];
                break;
            }
        }

        if (elem)
        {
            

        }
        else
        {
            UIElement button = {};

            button.id = id;
            button.x = x;
            button.y = y;
            button.width = w;
            button.height = h;
            button.type = ElementType::UI_BUTTON;

            gui.uiStates.push_back(button);
        }

        return true;
    }

    void initImguiImpl()
    {
        xe_graphics::GraphicsDevice *device = xe_render::getDevice();
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

    void startFrame()
    {
        xe_graphics::GraphicsDevice *device = xe_render::getDevice();
#ifdef GAPI_GL
        ImGui_ImplOpenGL3_NewFrame();
#endif // GAPI_GL

#ifdef GAPI_DX11
        ImGui_ImplDX11_NewFrame();
#endif
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }

    void endFrame()
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
