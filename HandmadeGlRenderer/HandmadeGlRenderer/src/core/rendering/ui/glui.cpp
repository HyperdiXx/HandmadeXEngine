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

void XEngine::GLGUI::setUIScene5(glm::vec3 &pos)
{
    static bool show = true;

   
    ImGui::Begin("XEngine Editor");
    ImGui::Text("Scene 1");

    //ImGui::SliderInt("Octaves", &octaves, 1, 20);
    ImGui::SliderFloat("Dir light position X", &pos.x, -100.0f, 100.0f);
    ImGui::SliderFloat("Dir light position Y", &pos.y, -100.0f, 100.0f);
    ImGui::SliderFloat("Dir light position Z", &pos.z, -100.0f, 100.0f);
    //ImGui::SliderFloat("Displacement factor", &dispFactor, 0.0f, std::pow(32.f*32.f*32.f, 1 / power));
    //ImGui::SliderFloat("Grass coverage", &grassCoverage, 0.0f, 1.f);
    //ImGui::SliderFloat("Tessellation multiplier", &tessMultiplier, 0.1f, 5.f);
    //ImGui::SliderFloat("Fog fall-off", &fogFalloff, 0.0f, 10.);
    //ImGui::SliderFloat("Power", &power, 0.0f, 10.);


    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

/*void XEngine::GLGUI::addEdit3()
{
    editLayer.push_back(0);
    
}*/

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


