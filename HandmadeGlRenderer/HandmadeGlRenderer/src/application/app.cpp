

#include <thread>
#include "app.h"

#include "../core/geometry/generator.h"
#include "../core/OpenGL/vao.h"

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

    
    void OpenGLRunEngineWin32()
    {
        
        std::cout << "OpenGLInitEngine\n";

        OpenGLWindowBuffer wb = {};
        InitOpenglWindow(&wb);

        XEngine::EngineGUI::InitGui(wb.window);

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

        Shader blurShader = {};
        Shader bloomShader = {};
        Shader mixedShader = {};

        Shader dispShader = {};

        Shader shaderGeometryPass = {}; 
        Shader shaderLightingPass = {}; 
        //Shader shaderLightBox = {}; ("8.1.deferred_light_box.vs", "8.1.deferred_light_box.fs");
        
        shaderGeometryPass.vs = "src/shaders/gBuffer.vs";
        shaderGeometryPass.fs = "src/shaders/gBuffer.fs";

        shaderLightingPass.vs = "src/shaders/defshading.vs";
        shaderLightingPass.fs = "src/shaders/defshading.fs";

        dispShader.vs = "src/shaders/parallaxmapping.vs";
        dispShader.fs = "src/shaders/parallaxmapping.fs";

        blurShader.vs = "src/shaders/blur.vs";
        blurShader.fs = "src/shaders/blur.fs";

        bloomShader.vs = "src/shaders/bloom.vs";
        bloomShader.fs = "src/shaders/bloom.fs";

        mixedShader.vs = "src/shaders/blendingshader.vs";
        mixedShader.fs = "src/shaders/blendingshader.fs";

        normalMappingShader.vs = "src/shaders/normalShader.vs";
        normalMappingShader.fs = "src/shaders/normalShader.fs";

        cubeMap.vs = "src/shaders/cubeMap.vs";
        cubeMap.fs = "src/shaders/cubeMap.fs";

        basicShader.vs = "src/shaders/basicShader.vs";
        basicShader.fs = "src/shaders/basicShader.fs";

        lightShader.vs = "src/shaders/bloom.vs";
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
        Win32SetShaderName(&blurShader);
        Win32SetShaderName(&bloomShader);
        Win32SetShaderName(&mixedShader);
        Win32SetShaderName(&dispShader);
        Win32SetShaderName(&shaderGeometryPass);
        Win32SetShaderName(&shaderLightingPass);


        std::vector<glm::vec3> objectPositions;
        objectPositions.push_back(glm::vec3(-3.0, 0.0, -3.0));
        objectPositions.push_back(glm::vec3(0.0, 0.0, -3.0));
        objectPositions.push_back(glm::vec3(3.0, 0.0, -3.0));
        objectPositions.push_back(glm::vec3(-3.0, 0.0, 0.0));
        objectPositions.push_back(glm::vec3(0.0, 0.0, 0.0));
        objectPositions.push_back(glm::vec3(3.0, 0.0, 0.0));
        objectPositions.push_back(glm::vec3(-3.0, 0.0, 3.0));
        objectPositions.push_back(glm::vec3(0.0, 0.0, 3.0));
        objectPositions.push_back(glm::vec3(3.0, 0.0, 3.0));

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
        

        GeometryBuffer plane;
        GeometryBuffer sky;
        plane.data = planeVertices;
        sky.data = skyboxVertices;
        createVertexBuffer(&plane);
        createVertexBuffer(&sky);

        /*std::vector<glm::vec3> lightPositions;
        lightPositions.push_back(glm::vec3(0.0f, 0.5f, 1.5f));
        lightPositions.push_back(glm::vec3(-4.0f, 0.5f, -3.0f));
        lightPositions.push_back(glm::vec3(3.0f, 0.5f, 1.0f));
        lightPositions.push_back(glm::vec3(-0.8f, 2.4f, -1.0f));

        std::vector<glm::vec3> lightColors;
        lightColors.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
        lightColors.push_back(glm::vec3(10.0f, 0.0f, 0.0f));
        lightColors.push_back(glm::vec3(0.0f, 0.0f, 15.0f));
        lightColors.push_back(glm::vec3(0.0f, 5.0f, 0.0f));*/

        

        //gBuffer creation

        uint32 GPos, GNormal, GSpeccolor, GBuffer, rboDepth;


        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        const unsigned int NR_LIGHTS = 32;
        std::vector<glm::vec3> lightPositions;
        std::vector<glm::vec3> lightColors;
        srand(13);
        for (unsigned int i = 0; i < NR_LIGHTS; i++)
        {
            // calculate slightly random offsets
            float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
            float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
            float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
            lightPositions.push_back(glm::vec3(xPos, yPos, zPos));
            // also calculate random color
            float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
            float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
            float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
            lightColors.push_back(glm::vec3(rColor, gColor, bColor));
        }

        XEngine::Cubemap cub;
        std::vector<std::string> textures;
        textures.push_back("src/textures/lakes_rt.tga");
        textures.push_back("src/textures/lakes_lf.tga");
        textures.push_back("src/textures/lakes_up.tga");
        textures.push_back("src/textures/lakes_dn.tga");
        textures.push_back("src/textures/lakes_ft.tga");
        textures.push_back("src/textures/lakes_bk.tga");

        cub.textures = std::move(textures);

        unsigned int diffuseMapTexture = XEngine::loadTexture("src/textures/desertsky_bk.tga");
        unsigned int specularMap = XEngine::loadTexture("src/textures/container2_specular.png");
        unsigned int cubemaptexture = XEngine::loadCubemap(cub.textures);
        unsigned int floorTexture = XEngine::loadTexture("src/textures/get.png");

        unsigned int diffuseMapForNormals = loadTexture("src/textures/bricks2.jpg");
        unsigned int normalMap = loadTexture("src/textures/bricks2_normal.jpg");
        unsigned int dispMap = loadTexture("src/textures/bricks2_disp.jpg");

        Win32UseShader(&dispShader);
        setInt(&dispShader, "diffuseMap", 0);
        setInt(&dispShader, "normalMap", 1);
        setInt(&dispShader, "depthMap", 2);

        Win32UseShader(&shaderGeometryPass);
        setInt(&shaderGeometryPass, "tex1", 0);
        setInt(&shaderGeometryPass, "tex2", 1);

        Win32UseShader(&shaderLightingPass);
        setInt(&shaderLightingPass, "GPos", 0);
        setInt(&shaderLightingPass, "GNormal", 1);
        setInt(&shaderLightingPass, "GSpeccolor", 2);

        

        /*Win32UseShader(&normalMappingShader);
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

        Win32UseShader(&bloomShader);
        setInt(&bloomShader, "diffuseMap", 0);
        Win32UseShader(&blurShader);
        setInt(&blurShader, "diffuseTexture", 0);
        Win32UseShader(&mixedShader);
        setInt(&mixedShader, "scene", 0);
        setInt(&mixedShader, "bloomBlur", 1);*/


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

        bool bloom = true;
        bool bloomKeyPressed = false;
        float exposure = 1.0f;
        while (!glfwWindowShouldClose(wb.window))
        {

            std::cout << "UpdateEngine\n";
            cam.speed = 2.5f * deltaTime;
            real64 currFrame = glfwGetTime();

            deltaTime = currFrame - lastFrame;
            lastFrame = currFrame;
                        
            XEngine::processInput(wb.window, &cam);
            //std::thread inp(XEngine::processInput, wb.window, &cam);
            //inp.detach();
            //inp.join();

            
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

          
            projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
            view = glm::mat4(XEngine::getViewMatrix(&cam));
            Win32UseShader(&dispShader);
            setMat4(&dispShader, "projection", projection);
            setMat4(&dispShader, "view", view);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show parallax mapping from multiple directions
            setMat4(&dispShader, "model", model);
            setVec3(&dispShader, "viewPos", cam.camPos);
            setVec3(&dispShader, "lightPos", lightPos);
            setFloat(&dispShader, "heightScale", 0.1);

            bindTexture2D(0, diffuseMapForNormals);
            bindTexture2D(1, normalMap);
            bindTexture2D(2, dispMap);

            renderQuad();

            // render light source (simply re-renders a smaller plane at the light's position for debugging/visualization)
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.1f));
            setMat4(&dispShader, "model", model);
            renderQuad();

            //skybox
            glDepthFunc(GL_LEQUAL);
            Win32UseShader(&cubeMap);
            view = glm::mat4(glm::mat3(XEngine::getViewMatrix(&cam)));
            setMat4(&cubeMap, "projection", projection);
            setMat4(&cubeMap, "view", view);
            glBindVertexArray(sky.vao);
            bindCubeTexture2D(0, cubemaptexture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
            glDepthFunc(GL_LESS);


            XEngine::EngineGUI::UpdateGui(wb.window,&gui);

            glfwSwapBuffers(wb.window);
            glfwPollEvents();
        }


        delGeometry(&plane);
        delGeometry(&sky);
        glDeleteVertexArrays(1, &cubeVAO);
        glDeleteBuffers(1, &cubeVBO);

        glfwTerminate();

    }

    void UpdateLoopWin32(OpenGLWindowBuffer* wb, XEngine::Camera *cam, Loop *lp)
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

glBindFramebuffer(GL_FRAMEBUFFER, 0);


glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
Win32UseShader(&shaderLightingPass);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, GPos);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, GNormal);
glActiveTexture(GL_TEXTURE2);
glBindTexture(GL_TEXTURE_2D, GSpeccolor);
for (unsigned int i = 0; i < lightPositions.size(); i++)
{
    setVec3(&shaderLightingPass, "lights[" + std::to_string(i) + "].pos", lightPositions[i]);
    setVec3(&shaderLightingPass, "lights[" + std::to_string(i) + "].color", lightColors[i]);

    const float constant = 1.0;
    const float linear = 0.7;
    const float quadratic = 1.8;
    setFloat(&shaderLightingPass, "lights[" + std::to_string(i) + "].linear", linear);
    setFloat(&shaderLightingPass, "lights[" + std::to_string(i) + "].quadratic", quadratic);
}
setVec3(&shaderLightingPass, "viewPos", cam.camPos);
renderQuad();

glBindFramebuffer(GL_READ_FRAMEBUFFER, GBuffer);
glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
// blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
// the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
// depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
glBlitFramebuffer(0, 0, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
glBindFramebuffer(GL_FRAMEBUFFER, 0);


//parallax mapping example




//lightPos.x = sin(glfwGetTime()) * 3.0f;
           //lightPos.z = cos(glfwGetTime()) * 2.0f;
           //lightPos.y = 5.0 + cos(glfwGetTime()) * 1.0f;


           /*glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

           projection = glm::perspective(glm::radians(45.0f), float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);
           view = glm::mat4(XEngine::getViewMatrix(&cam));
           model = glm::mat4(1.0f);

           Win32UseShader(&bloomShader);
           setMat4(&bloomShader, "projection", projection);
           setMat4(&bloomShader, "view", view);

           glActiveTexture(GL_TEXTURE0);
           glBindTexture(GL_TEXTURE_2D, diffuseMapTexture);

           for (uint16 i = 0; i < lightPositions.size(); ++i)
           {
               setVec3(&bloomShader, "light[" + std::to_string(i) + "].Pos", lightPositions[i]);
               setVec3(&bloomShader, "light[" + std::to_string(i) + "].Color", lightColors[i]);
           }

           setVec3(&bloomShader, "viewPos", cam.camPos);

           model = glm::mat4(1.0f);
           model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
           model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
           setMat4(&bloomShader, "model", model);
           setMat4(&bloomShader, "model", model);
           renderCube();

           glBindTexture(GL_TEXTURE_2D, specularMap);

           model = glm::mat4(1.0f);
           model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
           model = glm::scale(model, glm::vec3(0.5f));
           setMat4(&bloomShader, "model", model);
           renderCube();

           model = glm::mat4(1.0f);
           model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
           model = glm::scale(model, glm::vec3(0.5f));
           setMat4(&bloomShader, "model", model);
           renderCube();

           model = glm::mat4(1.0f);
           model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
           model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
           setMat4(&bloomShader, "model", model);
           renderCube();

           model = glm::mat4(1.0f);
           model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
           model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
           model = glm::scale(model, glm::vec3(1.25));
           setMat4(&bloomShader, "model", model);
           renderCube();

           model = glm::mat4(1.0f);
           model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
           model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
           setMat4(&bloomShader, "model", model);
           renderCube();

           model = glm::mat4(1.0f);
           model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
           model = glm::scale(model, glm::vec3(0.5f));
           setMat4(&bloomShader, "model", model);
           renderCube();

           // finally show all the light sources as bright cubes
           Win32UseShader(&lightShader);
           setMat4(&lightShader, "projection", projection);
           setMat4(&lightShader, "view", view);

           for (unsigned int i = 0; i < lightPositions.size(); i++)
           {
               model = glm::mat4(1.0f);
               model = glm::translate(model, glm::vec3(lightPositions[i]));
               model = glm::scale(model, glm::vec3(0.25f));
               setMat4(&lightShader, "model", model);
               setVec3(&lightShader, "lightColor", lightColors[i]);
               renderCube();
           }
           glBindFramebuffer(GL_FRAMEBUFFER, 0);

           bool hor = true, first_i = true;
           unsigned int amount = 10;

           Win32UseShader(&blurShader);
           for (unsigned int i = 0; i < amount; i++)
           {
               glBindFramebuffer(GL_FRAMEBUFFER, pingphongFBO[hor]);
               setInt(&blurShader, "hor", hor);
               glBindTexture(GL_TEXTURE_2D, first_i ? colorBuffers[1] : pingcolorBuffer[!hor]);  // bind texture of other framebuffer (or scene if first iteration)
               renderQuad();
               hor = !hor;
               if (first_i)
                   first_i = false;
           }
           glBindFramebuffer(GL_FRAMEBUFFER, 0);

           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
           Win32UseShader(&mixedShader);
           glActiveTexture(GL_TEXTURE0);
           glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
           glActiveTexture(GL_TEXTURE1);
           glBindTexture(GL_TEXTURE_2D, pingcolorBuffer[!hor]);
           setInt(&mixedShader, "bloom", bloom);
           setFloat(&mixedShader, "exposure", exposure);
           renderQuad();*/

           /* //plane
            Win32UseShader(&floorShader);

            setMat4(&floorShader, "projection", projection);
            setMat4(&floorShader, "view", view);

            setVec3(&floorShader, "viewPos", cam.camPos);
            setVec3(&floorShader, "lightPos", lightposfloor);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, floorTexture);

            glBindVertexArray(planeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);*/




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


