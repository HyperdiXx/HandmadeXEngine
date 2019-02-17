
/* 
    The Rendering Engine as Part of XEngine.
    OpenGL API 4.5 

    Features: Camera, Textures, MultiTextures, Lighting 

    TODO(vlad): Assimp, Logger, Redering Interfaces, ImGUI, Stencil, Blending,
        FaceCulling, FrameBuffers, Cubemap, Instancing, 
        Antialiasing, ShadowMapping, PointShadow, NormalMapping,
        ParallaxMapping, Bloom,
        Deffered rendering,
        Gamma Correctiom, HDR, SSAO, PBR
*/



#include <thread>
#include <future>
#include <thread>

#include "application/app.h"


int main(int argc, char** argv)
{
    InitEngineWin32();
   

    WindowBuffer wb = {};
    InitOpenglWindow(&wb);

    XEngine::EngineGUI::InitGui();
   
    glEnable(GL_DEPTH_TEST);

    Shader basicShader = {};
    Shader lightShader = {};
    Shader cubeMap = {};

    cubeMap.vs = "src/shaders/cubeMap.vs";
    cubeMap.fs = "src/shaders/cubeMap.fs";

    basicShader.vs = "src/shaders/basicShader.vs";
    basicShader.fs = "src/shaders/basicShader.fs";

    lightShader.vs = "src/shaders/light.vs";
    lightShader.fs = "src/shaders/light.fs";

    Win32SetShaderName(&cubeMap);
    Win32SetShaderName(&basicShader);
    Win32SetShaderName(&lightShader);
    
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

    float vertices[] = {
                         
         -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };

    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    XEngine::Cubemap cub;
    std::vector<std::string> textures;
    textures.push_back("src/textures/lakes_rt.tga");
    textures.push_back("src/textures/lakes_lf.tga");
    textures.push_back("src/textures/lakes_up.tga");
    textures.push_back("src/textures/lakes_dn.tga");
    textures.push_back("src/textures/lakes_ft.tga");
    textures.push_back("src/textures/lakes_bk.tga");

    cub.textures = std::move(textures);

    unsigned int cubemap = XEngine::loadCubemap(&cub);

    unsigned int diffuseMap = XEngine::loadTexture("src/textures/container2.png");
    unsigned int specularMap = XEngine::loadTexture("src/textures/container2_specular.png");

    Win32UseShader(&basicShader);
    setInt(&basicShader, "material.diffuse", 0);
    setInt(&basicShader, "material.specular", 1);

    Win32UseShader(&cubeMap);
    setInt(&cubeMap, "cubemap", 0);
  
    /*Model barrel = {};

    barrel.filename = "Models/barrels.fbx";

    loadModelopengl(&barrel);

    */
    real32 deltaTime = 0.0f;
    real32 lastFrame = 0.0f;

    XEngine::Camera cam;

    cam.camPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cam.camTarget = glm::vec3(0.0f, 0.0f, -1.0f);
    cam.camUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    glm::vec3 lightPos(0.0f, 0.0f, 2.5f);
    
    bool show_demo_window = true;
    bool show_another_window = false;
    //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    XEngine::EngineGUI::GraphicInterface gui = {};

    gui.locTime = 0.0f;



   
    while (!glfwWindowShouldClose(wb.window))
    {
       
        UpdateLoopWin32();
        cam.speed = 2.5f * deltaTime;
        real32 currFrame = glfwGetTime();

        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;

        XEngine::processInput(wb.window, &cam);
        //std::thread inp(XEngine::processInput, wb.window, &cam);
        //inp.join();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //lightPos.x = sin(glfwGetTime() / 2.0f) * 2.0f;
        //lightPos.y = cos(glfwGetTime() / 2.0f) * 1.0f;
        //lightPos.z = sin(glfwGetTime() / 2.0f) * 2.0f;
    
        projection = glm::perspective(glm::radians(45.0f), (real32)WIDTH / (real32)HEIGHT, 0.1f, 100.0f);
        view = XEngine::getViewMatrix(&cam);
                
        Win32UseShader(&basicShader);
        setVec3(&basicShader, "viewPos", cam.camPos);
        setFloat(&basicShader, "material.shininess", 64.0f);

        setVec3(&basicShader, "dirLight.direction", -0.2f, -1.0f, -0.3f);
        setVec3(&basicShader, "dirLight.ambient", 0.05f, 0.05f, 0.05f);
        setVec3(&basicShader, "dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        setVec3(&basicShader, "dirLight.specular", 0.5f, 0.5f, 0.5f);

        for (int i = 0; i < 4; ++i)
        {
            setVec3(&basicShader, "pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
            setVec3(&basicShader, "pointLights[" + std::to_string(i) +"].ambient", 0.05f, 0.05f, 0.05f);
            setVec3(&basicShader, "pointLights[" + std::to_string(i) + "].diffuse", 1.0f, 0.0f, 0.0f);
            setVec3(&basicShader, "pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
            setFloat(&basicShader, "pointLights[" + std::to_string(i) + "].c", 1.0f);
            setFloat(&basicShader, "pointLights[" + std::to_string(i) + "].linear", 0.09);
            setFloat(&basicShader, "pointLights[" + std::to_string(i) + "].quadratic", 0.032);
        }
        
        setVec3(&basicShader, "spotLight.position", cam.camPos);
        setVec3(&basicShader, "spotLight.direction", cam.camTarget);
        setVec3(&basicShader, "spotLight.ambient", 0.0f, 0.0f, 1.0f);
        setVec3(&basicShader, "spotLight.diffuse", 0.0f, 0.0f, 1.0f);
        setVec3(&basicShader, "spotLight.specular", 1.0f, 1.0f, 1.0f);
        setFloat(&basicShader, "spotLight.constant", 1.0f);
        setFloat(&basicShader, "spotLight.linear", 0.09);
        setFloat(&basicShader, "spotLight.quadratic", 0.032);
        setFloat(&basicShader, "spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        setFloat(&basicShader, "spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
            

        setMat4(&basicShader, "projection", projection);
        setMat4(&basicShader, "view", view);
        
        glm::mat4 model = glm::mat4(1.0f);
        setMat4(&basicShader, "model", model);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            setMat4(&basicShader, "model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        Win32UseShader(&lightShader);
        setMat4(&lightShader, "projection", projection);
        setMat4(&lightShader, "view", view);

        glBindVertexArray(lightVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); 
            setMat4(&lightShader, "model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glDepthFunc(GL_FALSE);
        Win32UseShader(&cubeMap);
        view = glm::mat4(glm::mat3(XEngine::getViewMatrix(&cam))); 
        setMat4(&cubeMap, "projection", projection);
        setMat4(&cubeMap, "view", view);

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
        glDepthFunc(GL_TRUE);

        XEngine::EngineGUI::UpdateGui(&gui);

        glfwSwapBuffers(wb.window);
        glfwPollEvents();
    }

   
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);


    glfwTerminate();
    return (0);
}

