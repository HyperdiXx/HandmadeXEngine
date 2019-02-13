#include "imguibase.h"

#include <GLFW/glfw3.h>
#include "../imguit/imgui.h"
#include "openglgui.h"


#if defined(_WIN64) 

namespace XEngine
{
    namespace EngineGUI
    {
        void InitGui()
        {
            ImGui::CreateContext();
            ImGui::StyleColorsDark();

            ImGuiIO& io = ImGui::GetIO();
            io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
            io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

            io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
            io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
            io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
            io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
            io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
            io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
            io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
            io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
            io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
            io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
            io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
            io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
            io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
            io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
            io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
            io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
            io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
            io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
            io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
            io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
            io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;


            ImGui_ImplOpenGL3_Init("#version 410");
        }

        void UpdateGui(GraphicInterface *gui)
        {
            ImGuiIO& io = ImGui::GetIO();
            io.DisplaySize = ImVec2(1280, 720);
            float t = (float)glfwGetTime();
            io.DeltaTime = gui->locTime > 0.0f ? (t - gui->locTime) : (1.0f / 60.0f);

            gui->locTime = t;

            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();

            static bool show = true;

            

            //ImGui::ShowDemoWindow(&show);

            static float f = 0.0f;
            static int counter = 0;
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

            ImGui::Begin("XEngine Editor");                          // Create a window called "Hello, world!" and append into it.


            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();

            

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        bool onMouseButtonPressed()
        {
            ImGuiIO& io = ImGui::GetIO();
            


            return false;
        }

        bool onMouseButtonReleased()
        {
            return false;
        }
        bool onWindowResized()
        {
            return false;
        }
        bool onMouseMovedEvent()
        {
            return false;
        }
        bool onMouseScrolledEvent()
        {
            return false;
        }
        bool onKeyboardPressed()
        {
            ImGuiIO& io = ImGui::GetIO();
            

            return false;
        }
        bool onKeyboardReleased()
        {
            return false;
        }
    }
   
}
#endif // !_WIN64
