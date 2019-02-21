


#include "app.h"

#include "../core/generator.h"

#ifdef _WIN64
namespace XEngine
{


    XEngine::Camera cam;

    


    void renderScene(Shader *shader, unsigned int &vao)
    {
        glm::mat4 model = glm::mat4(1.0f);
        setMat4(shader, "model", model);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // cubes
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
        model = glm::scale(model, glm::vec3(0.5f));
        setMat4(shader, "model", model);
        renderCube();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
        model = glm::scale(model, glm::vec3(0.5f));
        setMat4(shader, "model", model);
        renderCube();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
        model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
        model = glm::scale(model, glm::vec3(0.25));
        setMat4(shader, "model", model);
        renderCube();
    }

    
    void RunEngineWin32()
    {
        
        std::cout << "InitEngine\n";

        WindowBuffer wb = {};
        InitOpenglWindow(&wb);

        XEngine::EngineGUI::InitGui();

        InitStats();
        
        Shader basicShader = {};
        Shader lightShader = {};
        Shader cubeMap = {};
        Shader floorShader = {};
        Shader textShader = {};
        Shader lightMapShader = {};
        Shader depthMapQuad = {};
        Shader shadowShader = {};
        Shader normalMappingShader = {};

        normalMappingShader.vs = "src/shaders/normalShader.vs";
        normalMappingShader.fs = "src/shaders/normalShader.fs";

        cubeMap.vs = "src/shaders/cubeMap.vs";
        cubeMap.fs = "src/shaders/cubeMap.fs";

        basicShader.vs = "src/shaders/basicShader.vs";
        basicShader.fs = "src/shaders/basicShader.fs";

        lightShader.vs = "src/shaders/light.vs";
        lightShader.fs = "src/shaders/light.fs";

        floorShader.vs = "src/shaders/lightPhongnew.vs";
        floorShader.fs = "src/shaders/lightPhongnew.fs";

        textShader.vs = "src/shaders/text.vs";
        textShader.fs = "src/shaders/text.fs";

        depthMapQuad.vs = "src/shaders/depth.vs";
        depthMapQuad.fs = "src/shaders/depth.fs";

        lightMapShader.vs = "src/shaders/lightrender.vs";
        lightMapShader.fs = "src/shaders/lightrender.fs";

        shadowShader.vs = "src/shaders/basicshadows.vs";
        shadowShader.fs = "src/shaders/basicshadows.fs";

        Win32SetShaderName(&basicShader);
        Win32SetShaderName(&lightShader);
        Win32SetShaderName(&cubeMap);
        Win32SetShaderName(&floorShader);
        Win32SetShaderName(&lightMapShader);
        Win32SetShaderName(&depthMapQuad);
        Win32SetShaderName(&shadowShader);
        Win32SetShaderName(&normalMappingShader);


        float planeVertices[] = {
                        
             25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
            -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

             25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
            -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
             25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
        };

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
            glm::vec3(2.0f,  1.0f,  0.0f),
            glm::vec3(4.0f,  5.0f,  0.0f),
            glm::vec3(0.0f,  3.2f,  0.5f),
            glm::vec3(6.0f,  2.0f,  0.3f),
            glm::vec3(-2.4f, 0.4f,  0.5f),
            glm::vec3(-3.7f,  3.0f, 0.5f),
            glm::vec3(-41.3f,  2.0f,  0.5f),
            glm::vec3(-6.5f,  2.0f, -2.5f),
            glm::vec3(-8.5f,  0.2f, -1.5f),
            glm::vec3(15.3f,  1.0f, -1.5f)
        };

        glm::vec3 pointLightPositions[] = {
            glm::vec3(0.7f,  0.2f,  2.0f),
            glm::vec3(2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3(0.0f,  0.0f, -3.0f)
        };

        unsigned int planeVAO, planeVBO;
        glGenVertexArrays(1, &planeVAO);
        glGenBuffers(1, &planeVBO);
        glBindVertexArray(planeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindVertexArray(0);

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

        unsigned int skyboxVAO, skyboxVBO;
        glGenVertexArrays(1, &skyboxVAO);
        glBindVertexArray(skyboxVAO);

        glGenBuffers(1, &skyboxVBO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //generating depth map


        const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
        unsigned int depthMapFBO;
        glGenFramebuffers(1, &depthMapFBO);

        unsigned int depthMap;
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        // attach depth texture as FBO's depth buffer
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        
        unsigned int hdrFBO;
        glGenFramebuffers(1, &hdrFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

        unsigned int colorBuffers[2];
        glGenTextures(2, colorBuffers);

        for (uint32 i = 0; i < 2; ++i)
        {
            glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WIDTH, HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);

        }
        unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        glDrawBuffers(2, attachments);


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

        unsigned int diffuseMap = XEngine::loadTexture("src/textures/desertsky_bk.tga");
        unsigned int specularMap = XEngine::loadTexture("src/textures/container2_specular.png");
        unsigned int cubemaptexture = XEngine::loadCubemap(cub.textures);
        unsigned int floorTexture = XEngine::loadTexture("src/textures/get.png");

        unsigned int diffuseMapForNormals = loadTexture("src/textures/brickwall.jpg");
        unsigned int normalMap = loadTexture("src/textures/brickwall_normal.jpg");

        Win32UseShader(&normalMappingShader);
        setInt(&normalMappingShader, "diffuseMap", 0);
        setInt(&normalMappingShader, "normalMap", 1);

        Win32UseShader(&basicShader);
        setInt(&basicShader, "material.diffuse", 0);
        setInt(&basicShader, "material.specular", 1);

        Win32UseShader(&cubeMap);
        setInt(&cubeMap, "skybox", 0);

        Win32UseShader(&floorShader);
        setInt(&floorShader, "floorTexture", 0);

        Win32UseShader(&shadowShader);
        setInt(&shadowShader, "diffuseTexture", 0);
        setInt(&shadowShader, "shadowMap", 1);

        Win32UseShader(&depthMapQuad);
        setInt(&depthMapQuad, "depthMap", 0);


        /*Model barrel = {};

        barrel.filename = "Models/barrels.fbx";

        loadModelopengl(&barrel);

        */
        real64 deltaTime = 0.0f;
        real64 lastFrame = 0.0f;


        cam.camPos = glm::vec3(0.0f, 2.0f, 10.0f);
        cam.camTarget = glm::vec3(0.0f, 0.0f, -1.0f);
        cam.camUp = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        glm::vec3 lightPos(0.5f, 1.0f, 0.3f);
        glm::vec3 lightposfloor(0.0f, 4.0f, 0.0f);

        bool show_demo_window = true;
        bool show_another_window = false;

        XEngine::EngineGUI::GraphicInterface gui = {};

        gui.locTime = 0.0f;

        glm::vec3 point = glm::vec3(rand() % 20, 0.0, rand() % 20);
        glm::mat4 floormodel = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        float nearp = 1.0f, farp = 7.5f;
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearp, farp);
        glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 lightspaceMatrix = lightProjection * lightView;

        while (!glfwWindowShouldClose(wb.window))
        {

            std::cout << "UpdateEngine\n";
            cam.speed = 2.5f * deltaTime;
            real64 currFrame = glfwGetTime();

            deltaTime = currFrame - lastFrame;
            lastFrame = currFrame;
                        
            XEngine::processInput(wb.window, &cam);
            //std::thread inp(XEngine::processInput, wb.window, &cam);
            //inp.join();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //lightPos.x = sin(glfwGetTime()) * 3.0f;
            //lightPos.z = cos(glfwGetTime()) * 2.0f;
            //lightPos.y = 5.0 + cos(glfwGetTime()) * 1.0f;
           
            
            projection = glm::perspective(glm::radians(45.0f), float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);
            view = glm::mat4(XEngine::getViewMatrix(&cam));
            Win32UseShader(&normalMappingShader);
            setMat4(&normalMappingShader, "projection", projection);
            setMat4(&normalMappingShader, "view", view);

            model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
            setMat4(&normalMappingShader, "model", model);
            setVec3(&normalMappingShader, "viewPos", cam.camPos);
            setVec3(&normalMappingShader, "lightPos", lightPos);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMapForNormals);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, normalMap);
            renderQuad();

            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.1f));
            setMat4(&normalMappingShader, "model", model);
            renderQuad();

            

            //plane
            Win32UseShader(&floorShader);

            setMat4(&floorShader, "projection", projection);
            setMat4(&floorShader, "view", view);

            setVec3(&floorShader, "viewPos", cam.camPos);
            setVec3(&floorShader, "lightPos", lightposfloor);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, floorTexture);

            glBindVertexArray(planeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
           
            
            
          
            //skybox
            /*glDepthFunc(GL_LEQUAL);
            Win32UseShader(&cubeMap);
            view = glm::mat4(glm::mat3(XEngine::getViewMatrix(&cam)));
            setMat4(&cubeMap, "projection", projection);
            setMat4(&cubeMap, "view", view);

            glBindVertexArray(skyboxVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemaptexture);

            glDrawArrays(GL_TRIANGLES, 0, 36);

            glBindVertexArray(0);
            glDepthFunc(GL_LESS);*/

            /*
            lights
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
                glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 1);
            }*/


            
            //cubes
            /*glm::mat4 modelshadow = glm::mat4(1.0f);
            setMat4(&shadowShader, "model", modelshadow);
            glBindVertexArray(planeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            modelshadow = glm::mat4(1.0f);
            modelshadow = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
            modelshadow = glm::scale(model, glm::vec3(0.5f));
            setMat4(&shadowShader, "model", model);
            renderCube();*/


            /*Win32UseShader(&basicShader);

            setVec3(&basicShader, "viewPos", cam.camPos);
            setFloat(&basicShader, "material.shininess", 64.0f);

            setVec3(&basicShader, "dirLight.direction", -0.2f, -1.0f, -0.3f);
            setVec3(&basicShader, "dirLight.ambient", 0.05f, 0.05f, 0.05f);
            setVec3(&basicShader, "dirLight.diffuse", 1.0f, 0.1f, 0.1f);
            setVec3(&basicShader, "dirLight.specular", 0.5f, 0.5f, 0.5f);

            for (int i = 0; i < 4; ++i)
            {
                setVec3(&basicShader, "pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
                setVec3(&basicShader, "pointLights[" + std::to_string(i) + "].ambient", 0.05f, 0.05f, 0.05f);
                setVec3(&basicShader, "pointLights[" + std::to_string(i) + "].diffuse", 1.0f, 1.0f, 1.0f);
                setVec3(&basicShader, "pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
                setFloat(&basicShader, "pointLights[" + std::to_string(i) + "].c", 1.0f);
                setFloat(&basicShader, "pointLights[" + std::to_string(i) + "].linear", 0.09f);
                setFloat(&basicShader, "pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
            }

            setVec3(&basicShader, "spotLight.position", cam.camPos);
            setVec3(&basicShader, "spotLight.direction", cam.camTarget);
            setVec3(&basicShader, "spotLight.ambient", 0.0f, 0.0f, 1.0f);
            setVec3(&basicShader, "spotLight.diffuse", 0.0f, 0.0f, 1.0f);
            setVec3(&basicShader, "spotLight.specular", 1.0f, 1.0f, 1.0f);
            setFloat(&basicShader, "spotLight.constant", 1.0f);
            setFloat(&basicShader, "spotLight.linear", 0.09f);
            setFloat(&basicShader, "spotLight.quadratic", 0.032f);
            setFloat(&basicShader, "spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            setFloat(&basicShader, "spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


            setMat4(&basicShader, "projection", projection);
            setMat4(&basicShader, "view", view);

            glm::mat4 modeln = glm::mat4(1.0f);
            setMat4(&basicShader, "model", modeln);

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
                glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 1);
            }
            */


            XEngine::EngineGUI::UpdateGui(&gui);

            glfwSwapBuffers(wb.window);
            glfwPollEvents();
        }


        glDeleteVertexArrays(1, &VAO);
        glDeleteVertexArrays(1, &lightVAO);
        glDeleteVertexArrays(1, &skyboxVAO);
        glDeleteVertexArrays(1, &planeVAO);
        glDeleteVertexArrays(1, &cubeVAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &skyboxVBO);
        glDeleteBuffers(1, &planeVBO);
        glDeleteBuffers(1, &cubeVBO);

        glfwTerminate();

    }

    void UpdateLoopWin32(WindowBuffer* wb, XEngine::Camera *cam, Loop *lp)
    {


    }

    void InitStats()
    {
        //glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);


    }

    void RenderQ(Shader *shader)
    {
        
    }
}
   

#endif



#if 0
Win32UseShader(&lightMapShader);
setMat4(&lightMapShader, "lightmatrix", lightspaceMatrix);

glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

glClear(GL_DEPTH_BUFFER_BIT);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, floorTexture);

//render

renderScene(&lightMapShader, planeVAO);

glBindFramebuffer(GL_FRAMEBUFFER, 0);

glViewport(0, 0, WIDTH, HEIGHT);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glViewport(0, 0, WIDTH, HEIGHT);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

Win32UseShader(&shadowShader);
projection = glm::perspective(glm::radians(45.0f), (real32)WIDTH / (real32)HEIGHT, 0.1f, 100.0f);
view = XEngine::getViewMatrix(&cam);

setMat4(&shadowShader, "projection", projection);
setMat4(&shadowShader, "view", view);

setVec3(&shadowShader, "viewPos", cam.camPos);
setVec3(&shadowShader, "lightPos", lightPos);
setMat4(&shadowShader, "lightSpaceMatrix", lightspaceMatrix);

glActiveTexture(GL_TEXTURE0);
glBindTexture(TEXTURE2D, floorTexture);
glActiveTexture(GL_TEXTURE1);
glBindTexture(TEXTURE2D, depthMap);

renderScene(&shadowShader, planeVAO);

Win32UseShader(&depthMapQuad);
setFloat(&depthMapQuad, "near_plane", nearp);
setFloat(&depthMapQuad, "far_plane", farp);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, depthMap);
#endif


