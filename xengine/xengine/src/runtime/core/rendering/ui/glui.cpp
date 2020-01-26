#include "glui.h"

#include <runtime/core/utility/log.h>

void XEngine::GLui::init(GLFWwindow* window, int theme)
{
    m_window = window;
    glEnable(GL_DEPTH_TEST);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    const char* glsl_version = "#version 330";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    if (theme == Style::DARK)    
        set_dark_theme();
    else    
        set_light_theme();
}

void XEngine::GLui::new_frame()
{    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void XEngine::GLui::update(vec4f& spritecol)
{
    static bool show = true;

    static float f = 0.0f;
    static int counter = 0;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    float col1[3] = { spritecol.x, spritecol.y, spritecol.z };

    ImGui::Begin("XEngine Editor");

    for (auto a : editLayer)
    {
        ImGui::ColorEdit3("Color edit", col1);
        spritecol.x = col1[0];
        spritecol.y = col1[1];
        spritecol.z = col1[2];
    }

    if (ImGui::Button("Add color!"))
        editLayer.push_back(0);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void XEngine::GLui::setUIScene5(vec3f &pos, vec4f &color, unsigned int texture, vec4f &colo1, vec4f &clor2, vec4f color3, bool &pressed)
{
    static bool show = true;

    float col1[3] = { color.x, color.y, color.z };
    float col2[3] = { colo1.x, colo1.y, colo1.z };
    float col3[3] = { clor2.x, clor2.y, clor2.z };
    float col4[3] = { color3.x, color3.y, color3.z };
   
    ImGui::Begin("XEngine Editor");
    ImGui::Text("Scene 1");

    ImGui::SliderFloat("Dir light position X", &pos.x, -100.0f, 100.0f);
    ImGui::SliderFloat("Dir light position Y", &pos.y, -100.0f, 100.0f);
    ImGui::SliderFloat("Dir light position Z", &pos.z, -100.0f, 100.0f);

    ImGui::ColorEdit3("Color edit", col1);
    color.x = col1[0];
    color.y = col1[1];
    color.z = col1[2];

    ImGui::ColorEdit3("Color edit box", col2);
    colo1.x = col2[0];
    colo1.y = col2[1];
    colo1.z = col2[2];

    ImGui::ColorEdit3("Color edit box", col3);
    clor2.x = col3[0];
    clor2.y = col3[1];
    clor2.z = col3[2];

    ImGui::ColorEdit3("Color edit box", col4);
    color3.x = col4[0]; 
    color3.y = col4[1];
    color3.z = col4[2];

    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Current bound texture");
    ImGui::Image((void*)(intptr_t)texture, ImVec2(64, 64));

    ImGui::Checkbox("Framebuffer", &pressed);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void XEngine::GLui::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void XEngine::GLui::top_bar()
{   
    bool show_log = true;
    bool *open = &show_log;
    if (ImGui::BeginMainMenuBar())
    {        
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O", false))            
                Log::info("Pressed on menu bar!");

            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Animation"))
        {
            if (ImGui::MenuItem("AnimTree", NULL, false))
            {
                Log::info("Pressed on animation tree window");
                ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
                ImGui::Begin("Example: Log", open);
                ImGui::End();
            }
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Options"))
        {
            if (ImGui::MenuItem("Help", NULL, false))
                Log::info("Pressed on help window");
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void XEngine::GLui::post_update()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void XEngine::GLui::set_dark_theme()
{
    ImGui::StyleColorsDark();
}

void XEngine::GLui::set_light_theme()
{
    ImGui::StyleColorsLight();
}

void XEngine::GLui::set_classic_theme()
{
    ImGui::StyleColorsClassic();
}


