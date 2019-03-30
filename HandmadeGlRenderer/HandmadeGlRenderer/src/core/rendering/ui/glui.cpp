#include "glui.h"



void XEngine::GLGUI::init(GLFWwindow* window, int theme)
{
    glEnable(GL_DEPTH_TEST);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    const char* glsl_version = "#version 330";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    if (theme == 1)
    {
        setDarkTheme();
    }
    else
    {
        setLightTheme();
    }
}

void XEngine::GLGUI::startUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void XEngine::GLGUI::update(glm::vec4& spritecol)
{
    static bool show = true;

    static float f = 0.0f;
    static int counter = 0;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::Begin("XEngine Editor");
    float col1[3] = { spritecol.x, spritecol.y, spritecol.z };
    ImGui::ColorEdit3("Sprite color", col1);

    spritecol.x = col1[0];
    spritecol.y = col1[1];
    spritecol.z = col1[2];

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


}

void XEngine::GLGUI::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void XEngine::GLGUI::setDarkTheme()
{
    ImGui::StyleColorsDark();
}

void XEngine::GLGUI::setLightTheme()
{
    ImGui::StyleColorsLight();
}

void XEngine::GLGUI::setClassicTheme()
{
    ImGui::StyleColorsClassic();
}


