#include "skybox.h"

#include "../core/rendering/scenes/sceneObjects.h"

using namespace XEngine;
using namespace Rendering;


XEngine::Rendering::Skybox::Skybox()
{
    sky = (GeometryBuffer*)malloc(sizeof(GeometryBuffer));
    tex = new Cubemap();
}

XEngine::Rendering::Skybox::Skybox(Shader * skyshader)
{
    float skyboxVertices[] = {

                 -1.0f,  1.0f, -1.0f,
                 -1.0f, -1.0f, -1.0f,
                  1.0f, -1.0f, -1.0f,
                  1.0f, -1.0f, -1.0f,
                  1.0f,  1.0f, -1.0f,
                 -1.0f,  1.0f, -1.0f,

                 -1.0f, -1.0f,  1.0f,
                 -1.0f, -1.0f, -1.0f,
                 -1.0f,  1.0f, -1.0f,
                 -1.0f,  1.0f, -1.0f,
                 -1.0f,  1.0f,  1.0f,
                 -1.0f, -1.0f,  1.0f,

                  1.0f, -1.0f, -1.0f,
                  1.0f, -1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f, -1.0f,
                  1.0f, -1.0f, -1.0f,

                 -1.0f, -1.0f,  1.0f,
                 -1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f, -1.0f,  1.0f,
                 -1.0f, -1.0f,  1.0f,

                 -1.0f,  1.0f, -1.0f,
                  1.0f,  1.0f, -1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                 -1.0f,  1.0f,  1.0f,
                 -1.0f,  1.0f, -1.0f,

                 -1.0f, -1.0f, -1.0f,
                 -1.0f, -1.0f,  1.0f,
                  1.0f, -1.0f, -1.0f,
                  1.0f, -1.0f, -1.0f,
                 -1.0f, -1.0f,  1.0f,
                  1.0f, -1.0f,  1.0f
    };

    VAO = new VertexArray();

    VAO->addBuffer(VBO, 0);
}

XEngine::Rendering::Skybox::~Skybox()
{
    
        glDeleteVertexArrays(1, &sky->vao);
        glDeleteBuffers(1, &sky->vbo);
        free(sky);
        delete(tex);
    
}

void Skybox::createSkybox()
{
    float skyboxVertices[] = {

                 -1.0f,  1.0f, -1.0f,
                 -1.0f, -1.0f, -1.0f,
                  1.0f, -1.0f, -1.0f,
                  1.0f, -1.0f, -1.0f,
                  1.0f,  1.0f, -1.0f,
                 -1.0f,  1.0f, -1.0f,

                 -1.0f, -1.0f,  1.0f,
                 -1.0f, -1.0f, -1.0f,
                 -1.0f,  1.0f, -1.0f,
                 -1.0f,  1.0f, -1.0f,
                 -1.0f,  1.0f,  1.0f,
                 -1.0f, -1.0f,  1.0f,

                  1.0f, -1.0f, -1.0f,
                  1.0f, -1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f, -1.0f,
                  1.0f, -1.0f, -1.0f,

                 -1.0f, -1.0f,  1.0f,
                 -1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f, -1.0f,  1.0f,
                 -1.0f, -1.0f,  1.0f,

                 -1.0f,  1.0f, -1.0f,
                  1.0f,  1.0f, -1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                 -1.0f,  1.0f,  1.0f,
                 -1.0f,  1.0f, -1.0f,

                 -1.0f, -1.0f, -1.0f,
                 -1.0f, -1.0f,  1.0f,
                  1.0f, -1.0f, -1.0f,
                  1.0f, -1.0f, -1.0f,
                 -1.0f, -1.0f,  1.0f,
                  1.0f, -1.0f,  1.0f
    };

   
    mtextures.push_back("src/textures/right.jpg");
    mtextures.push_back("src/textures/left.jpg");
    mtextures.push_back("src/textures/top.jpg");
    mtextures.push_back("src/textures/bottom.jpg");
    mtextures.push_back("src/textures/front.jpg");
    mtextures.push_back("src/textures/back.jpg");

    
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    sky->vao = skyboxVAO;
    sky->vbo = skyboxVBO;

    //cubemaptexture = tex->loadTextureCubemap(mtextures);
    tex->loadFromFiles(mtextures);

}


void Skybox::renderSkybox(Shader *shader, glm::mat4& v, glm::mat4& proj)
{
    tex->setDepthFunc(GL_LEQUAL);
    shader->enableShader();
    v = glm::mat3(v);
    shader->setMat4("projection", proj);
    shader->setMat4("view", v);
    glBindVertexArray(sky->vao);
    tex->bind(cubemaptexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    tex->setDepthFunc(GL_LESS);
}

XEngine::Rendering::SkyboxProced::SkyboxProced()
{
    skyColorTop = glm::vec3(0.5, 0.7, 0.8)*1.05f;
    skyColorBottom = glm::vec3(0.9, 0.9, 0.95);

    skyboxShader = new ScreenSpaceShader("shaders/sky.frag");
    skyboxFBO = new GLFrameBuffer(WINDOWWIDTH, WINDOWHEIGHT);

    SunsetPreset1();
    DefaultPreset();
}

XEngine::Rendering::SkyboxProced::~SkyboxProced()
{



}

void XEngine::Rendering::SkyboxProced::draw()
{
    SceneObjects &scene = SceneObjects::getInstance();
    skyboxFBO->bind();

    /*Shader& shader = skyboxShader->getShader();
    shader.enableShader();

    shader.setVec2("resolution", glm::vec2(WINDOWWIDTH, WINDOWHEIGHT));
    shader.setMat4("inv_proj", glm::inverse(scene.projMatrix));
    shader.setMat4("inv_view", glm::inverse(scene.cam->getViewMatrix()));

    shader.setVec3("lightDirection", glm::normalize(scene.lightPos - scene.cam->camPos));

    shader.setVec3("skyColorTop", skyColorTop);
    shader.setVec3("skyColorBottom", skyColorBottom);

    skyboxShader->draw();*/
}

void XEngine::Rendering::SkyboxProced::update()
{
    SceneObjects &scene = SceneObjects::getInstance();
    auto sigmoid = [](float v) { return 1 / (1.0 + exp(8.0 - v * 40.0)); };
    //mixSkyColorPreset(sigmoid(scene.lightDir.y), highSunPreset, presetSunset);
}

colorPreset XEngine::Rendering::SkyboxProced::DefaultPreset()
{
    colorPreset preset;

    preset.cloudColorBottom = (glm::vec3(65., 70., 80.)*(1.5f / 255.f));

    preset.skyColorTop = glm::vec3(0.5, 0.7, 0.8)*1.05f;
    preset.skyColorBottom = glm::vec3(0.9, 0.9, 0.95);

    preset.lightColor = glm::vec3(255, 255, 230) / 255.f;
    preset.fogColor = glm::vec3(0.5, 0.6, 0.7);

    highSunPreset = preset;

    return preset;
}

colorPreset XEngine::Rendering::SkyboxProced::SunsetPreset()
{
    colorPreset preset;

    preset.cloudColorBottom = glm::vec3(89, 96, 109) / 255.f;
    preset.skyColorTop = glm::vec3(177, 174, 119) / 255.f;
    preset.skyColorBottom = glm::vec3(234, 125, 125) / 255.f;

    preset.lightColor = glm::vec3(255, 171, 125) / 255.f;
    preset.fogColor = glm::vec3(85, 97, 120) / 255.f;

    presetSunset = preset;

    return preset;
}

colorPreset XEngine::Rendering::SkyboxProced::SunsetPreset1()
{
    colorPreset preset;

    preset.cloudColorBottom = glm::vec3(97, 98, 120) / 255.f;
    preset.skyColorTop = glm::vec3(133, 158, 214) / 255.f;
    preset.skyColorBottom = glm::vec3(241, 161, 161) / 255.f;

    preset.lightColor = glm::vec3(255, 201, 201) / 255.f;
    preset.fogColor = glm::vec3(128, 153, 179) / 255.f;

    presetSunset = preset;

    return preset;
}

void XEngine::Rendering::SkyboxProced::mixSkyColorPreset(float v, colorPreset p1, colorPreset p2)
{
    SceneObjects &scene = SceneObjects::getInstance();

    float a = std::min(std::max(v, 0.0f), 1.0f);
    float b = 1.0 - a;

    //cloudColorBottom = p1.cloudColorBottom*a + p2.cloudColorBottom*b;
    skyColorTop = p1.skyColorTop*a + p2.skyColorTop*b;
    skyColorBottom = p1.skyColorBottom*a + p2.skyColorBottom*b;
    //scene.lightColor = p1.lightColor*a + p2.lightColor*b;
    scene.fogColor = p1.fogColor*a + p2.fogColor*b;
}

