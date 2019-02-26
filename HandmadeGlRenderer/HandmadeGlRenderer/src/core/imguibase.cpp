#include "imguibase.h"

#include <GLFW/glfw3.h>
#include "../imguit/imgui.h"
#include "openglgui.h"


#if defined(_WIN64) 

namespace XEngine
{
    namespace EngineGUI
    {
        void InitGui(GLFWwindow* window)
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

            g_MouseCursors[ImGuiMouseCursor_Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
            g_MouseCursors[ImGuiMouseCursor_TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
            g_MouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);   // FIXME: GLFW doesn't have this.
            g_MouseCursors[ImGuiMouseCursor_ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
            g_MouseCursors[ImGuiMouseCursor_ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
            g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);  // FIXME: GLFW doesn't have this.
            g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);  // FIXME: GLFW doesn't have this.
            g_MouseCursors[ImGuiMouseCursor_Hand] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);

            // Chain GLFW callbacks: our callbacks will call the user's previously installed callbacks, if any.
            g_PrevUserCallbackMousebutton = NULL;
            g_PrevUserCallbackScroll = NULL;
            g_PrevUserCallbackKey = NULL;
            g_PrevUserCallbackChar = NULL;
            g_PrevUserCallbackMousebutton = glfwSetMouseButtonCallback(window, onMouseButtonPressed);

            if (true)
            {
                //g_PrevUserCallbackScroll = glfwSetScrollCallback(window, ImGui_ImplGlfw_ScrollCallback);
                //g_PrevUserCallbackKey = glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
                //g_PrevUserCallbackChar = glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);
            }

            ImGui_ImplOpenGL3_Init("#version 410");
        }

        void UpdateGui(GLFWwindow *window, GraphicInterface *gui)
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

            mouseUpdatePos(window);
            updateMouseCursor(window);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        void onMouseButtonPressed(GLFWwindow* window, int button, int action, int mods)
        {
           if (g_PrevUserCallbackMousebutton != NULL)
                    g_PrevUserCallbackMousebutton(window, button, action, mods);

           if (action == GLFW_PRESS && button >= 0 && button < IM_ARRAYSIZE(g_MouseJustPressed))
                    g_MouseJustPressed[button] = true;
               
        }

        void mouseUpdatePos(GLFWwindow* window)
        {
            // Update buttons
            ImGuiIO& io = ImGui::GetIO();
            for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
            {
                // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
                io.MouseDown[i] = g_MouseJustPressed[i] || glfwGetMouseButton(window, i) != 0;
                g_MouseJustPressed[i] = false;
            }

            // Update mouse position
            const ImVec2 mouse_pos_backup = io.MousePos;
            io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
#ifdef __EMSCRIPTEN__
            const bool focused = true; // Emscripten
#else
            const bool focused = glfwGetWindowAttrib(window, GLFW_FOCUSED) != 0;
#endif
            if (focused)
            {
                if (io.WantSetMousePos)
                {
                    glfwSetCursorPos(window, (double)mouse_pos_backup.x, (double)mouse_pos_backup.y);
                }
                else
                {
                    double mouse_x, mouse_y;
                    glfwGetCursorPos(window, &mouse_x, &mouse_y);
                    io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);
                }
            }
        }

        void updateMouseCursor(GLFWwindow* window)
        {
            ImGuiIO& io = ImGui::GetIO();
            if ((io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) || glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
                return;

            ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
            if (imgui_cursor == ImGuiMouseCursor_None || io.MouseDrawCursor)
            {
                // Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            }
            else
            {
                // Show OS mouse cursor
                // FIXME-PLATFORM: Unfocused windows seems to fail changing the mouse cursor with GLFW 3.2, but 3.3 works here.
                glfwSetCursor(window, g_MouseCursors[imgui_cursor] ? g_MouseCursors[imgui_cursor] : g_MouseCursors[ImGuiMouseCursor_Arrow]);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
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
        void Shutdown()
        {

        }
    }
   
}
#endif // !_WIN64
