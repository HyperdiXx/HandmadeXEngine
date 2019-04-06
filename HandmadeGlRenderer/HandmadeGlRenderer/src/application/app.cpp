

#include <thread>
#include "app.h"

#include "../core/geometry/generator.h"
#include "../objects/skybox.h"
#include "../core/utility/log.h"

#include "../core/rendering/openglnew/renderer2d.h"
#include "../core/rendering/openglnew/batchrenderer.h"

#include "../core/rendering/sprite.h"
#include "../core/rendering/batchsprite.h"

#include "../core/rendering/ui/glui.h"

#include "../core/utility/clock.h"


#include "../core/rendering/pipeline/shader.h"

#include "../core/rendering/texture.h"

#include "../core/systems/textureload.h"
#include "../core/geometry/model.h"

#include "../core/rendering/text.h"
#include "../core/windowsystem/windowWin.h"

#include "../core/windowsystem/openglwnd.h"



#define BATCH 0

#ifdef _WIN64
namespace XEngine
{

    void Application::OpenGLRunEngineWin32()
    {

        Rendering::WindowGL classicwindow("XEngine", WINDOWWIDTH, WINDOWHEIGHT);

        classicwindow.initStats();

        XEngine::GLGUI myUi(classicwindow.m_window, 1);
        
        XEngine::CameraU::Camera camera;

        Shader basicShader("src/shaders/basicShader.vs", "src/shaders/basicShader.fs");

        Shader lightShader("src/shaders/bloom.vs", "src/shaders/light.fs");
        Shader cubeMap("src/shaders/cubeMap.vs", "src/shaders/cubeMap.fs");
        Shader floorShader("src/shaders/lightPhongnew.vs", "src/shaders/lightPhongnew.fs");
        Shader textShader("src/shaders/text.vs", "src/shaders/text.fs");
        Shader lightMapShader("src/shaders/lightrender.vs", "src/shaders/lightrender.fs");
        Shader depthMapQuad("src/shaders/depth.vs", "src/shaders/depth.fs");
        Shader shadowShader("src/shaders/basicshadows.vs", "src/shaders/basicshadows.fs");
        Shader normalMappingShader("src/shaders/normalShader.vs", "src/shaders/normalShader.fs");

        Shader blurShader("src/shaders/blur.vs", "src/shaders/blur.fs");
        Shader bloomShader("src/shaders/bloom.vs", "src/shaders/bloom.fs");
        Shader mixedShader("src/shaders/blendingshader.vs", "src/shaders/blendingshader.fs");

        Shader dispShader("src/shaders/parallaxmapping.vs", "src/shaders/parallaxmapping.fs");

        Shader shaderGeometryPass("src/shaders/gBuffer.vs", "src/shaders/gBuffer.fs");
        Shader shaderLightingPass("src/shaders/defshading.vs", "src/shaders/defshading.fs");
       //Shader shaderLightBox = {}; ("8.1.deferred_light_box.vs", "8.1.deferred_light_box.fs");

        basicShader.setupShaderFile();
        lightShader.setupShaderFile();
        cubeMap.setupShaderFile();
        floorShader.setupShaderFile();
        lightMapShader.setupShaderFile();
        depthMapQuad.setupShaderFile();
        shadowShader.setupShaderFile();
        normalMappingShader.setupShaderFile();
        blurShader.setupShaderFile();
        bloomShader.setupShaderFile();
        mixedShader.setupShaderFile();
        dispShader.setupShaderFile();
        shaderGeometryPass.setupShaderFile();
        shaderLightingPass.setupShaderFile();
        textShader.setupShaderFile();

        GeometryBuffer plane;
        std::vector<float> planeVertices = createPlane();

        createVertexBuffer(&plane, planeVertices);

        XEngine::Rendering::Skybox sky;
        sky.createSkybox();

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        XEngine::Cubemap cub;
        std::vector<std::string> textures;
        textures.push_back("src/textures/sahara_rt.tga");
        textures.push_back("src/textures/sahara_lf.tga");
        textures.push_back("src/textures/sahara_up.tga");
        textures.push_back("src/textures/sahara_dn.tga");
        textures.push_back("src/textures/sahara_ft.tga");
        textures.push_back("src/textures/sahara_bk.tga");

        cub.textures = std::move(textures);

        unsigned int diffuseMapTexture = XEngine::Utils::loadTexture("src/textures/desertsky_bk.tga");
        unsigned int specularMap = XEngine::Utils::loadTexture("src/textures/container2_specular.png");
        unsigned int cubemaptexture = XEngine::Utils::loadCubemap(cub.textures);
        unsigned int floorTexture = XEngine::Utils::loadTexture("src/textures/get.png");

        unsigned int diffuseMapForNormals = XEngine::Utils::loadTexture("src/textures/bricks2.jpg");
        unsigned int normalMap = XEngine::Utils::loadTexture("src/textures/bricks2_normal.jpg");
        unsigned int dispMap = XEngine::Utils::loadTexture("src/textures/bricks2_disp.jpg");

        //unsigned int nanosuuitalbedo = loadTexture("src/textures/arm_dif.png");
        //unsigned int nanosuuitalbedo2 = loadTexture("src/textures/arm_dif.png");

       
        
        dispShader.enableShader();
        dispShader.setInt("diffuseMap", 0);
        dispShader.setInt("normalMap", 1);
        dispShader.setInt("depthMap", 2);

        shaderGeometryPass.enableShader();
        shaderGeometryPass.setInt("tex1", 0);
        shaderGeometryPass.setInt("tex2", 1);

        //gbuffer shader
        /*shaderLightingPass.enableShader();
        shaderLightingPass.setInt("GPos", 0);
        shaderLightingPass.setInt("GNormal", 1);
        shaderLightingPass.setInt("GSpeccolor", 2);*/

        cubeMap.enableShader();
        cubeMap.setInt("skybox", 0);

        floorShader.enableShader();
        floorShader.setInt("floorTexture", 0);

        /*Win32UseShader(&normalMappingShader);
        setInt(&normalMappingShader, "diffuseMap", 0);
        setInt(&normalMappingShader, "normalMap", 1);

        Win32UseShader(&basicShader);
        setInt(&basicShader, "material.diffuse", 0);
        setInt(&basicShader, "material.specular", 1);

        Win32UseShader(&cubeMap);
        setInt(&cubeMap, "skybox", 0);


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
        setInt(&mixedShader, "bloomBlur", 1)*/


        //Assets::Model firstmodel("src/models/barrels/barrels.fbx", false);
        Assets::Model secondmodel("src/models/nano/nanosuit.obj", false);
        Assets::Model cityModel("src/models/house/house2.obj", false);
        Assets::Model sponza("src/models/sponza/sponza.obj", false);
      
        real64 deltaTime = 0.0f;
        real64 lastFrame = 0.0f;

       
        glm::mat4 floormodel = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        glm::vec3 lightPos(0.5f, 1.0f, 0.3f);
        glm::vec3 lightposfloor(0.0f, 4.0f, 0.0f);

        glm::vec3 point = glm::vec3(rand() % 20, 0.0, rand() % 20);

        bool bloom = true;
        bool bloomKeyPressed = false;
        float exposure = 1.0f;

        glm::mat4 mvp = glm::mat4(1.0f);
        float nearp = 1.0f, farp = 7.5f;
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearp, farp);
        glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 lightspaceMatrix = lightProjection * lightView;
            
        //XEngine::Camera cam;

        Clock clockm, time;
        float ctime = 0;
        unsigned int frames = 0;

        XEngine::Rendering::Font text1("src/fonts/arial.ttf", &textShader);

        glm::mat4 orho = glm::mat4(1.0f);

        orho = glm::ortho(0.0f, float(WINDOWWIDTH), 0.0f, float(WINDOWHEIGHT), -1.0f, 1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)WINDOWWIDTH / (float)WINDOWHEIGHT, 0.1f, 400.0f);


        Shader shadersprite("src/shaders/basic2d.vs", "src/shaders/basic2d.fs");
        Shader loading("src/shaders/simplemodel.vs", "src/shaders/simplemodel.fs");


        loading.setupShaderFile();
        
        glm::mat4 modelforsprite = glm::mat4(1.0f);
        modelforsprite = glm::translate(modelforsprite, glm::vec3(0.0f, 10.0f, 0.0f));

        shadersprite.setupShaderFile();

        shadersprite.enableShader();
        shadersprite.setMat4("projection", orho);

        loading.enableShader();
        loading.setMat4("projection", projection);

        glm::vec4 spriteColor = glm::vec4(1.0, 0.0, 0.0, 1.0);
        glm::vec4 spriteColor2 = glm::vec4(1.0, 1.0, 0.0, 1.0);

        using namespace Rendering;

#if BATCH
        BatchSprite testsprite(100, 100, 40, 40, spriteColor);
        BatchSprite testsprite2(500, 500, 100, 100, spriteColor2);
        BatchRenderer2d renderer;
#else
        Sprite testsprite(100, 100, 500, 40, spriteColor, shadersprite);
        Sprite testsprite2(500, 500, 100, 100, spriteColor2, shadersprite);
        Renderer2d renderer;
#endif

        

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        while (!classicwindow.isClosed())
        {
            LOG("\rUpdateLoop...");
            

            camera.speed = 10.0f * deltaTime;

            real64 currFrame = glfwGetTime();

            deltaTime = currFrame - lastFrame;
            lastFrame = currFrame;

            XEngine::processInput(classicwindow.m_window, &camera);

            //std::thread inp(XEngine::processInput, wb.window, &cam);
            //inp.detach();
            //inp.join();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            myUi.startUpdate();
                       
            loading.enableShader();
            view = camera.getViewMatrix();
            loading.setMat4("view", view);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
            loading.setMat4("model", model);
            sponza.drawMesh(&loading);

           /* glm::mat4 model1 = glm::mat4(1.0f);
            model1 = glm::translate(model1, glm::vec3(-10.0f, 0.0f, 0.0f));
            model1 = glm::scale(model1, glm::vec3(0.2f, 0.2f, 0.2f));
            loading.setMat4("model", model1);
            cityModel.drawMesh(&loading);*/
            

            shadersprite.enableShader();
            shadersprite.setVec4("color", spriteColor);
#if BATCH
            renderer.start();
#endif
            renderer.submit(&testsprite);
            renderer.submit(&testsprite2);

#if BATCH
            renderer.end();
#endif
            renderer.flush();

            sky.renderSkybox(&cubeMap, &camera, view, projection, cubemaptexture);

            myUi.update(spriteColor);
            
            text1.updateText("FPS: " + std::to_string(frames), 10.0f, 700.0f, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));

            classicwindow.update();

            ++frames;

            if (time.elapsed() - ctime > 1.0f)
            {
                ctime += 1.0f;
                //std::cout << "\n" << frames << "fps\n";
                frames = 0;
            }
        }
        
        delGeometry(&plane);
        delGeometry(sky.getGeometryBuffer());

        glDeleteVertexArrays(1, &cubeVAO);
        glDeleteBuffers(1, &cubeVBO);

        myUi.shutdown();
       

        glfwTerminate();
       
    }

    void Application::DX11InitEngine()
    {
        Rendering::WindowDX dxwnd;

        dxwnd.initEngine();

        LOG("XEngine v 0.0.1");

        dxwnd.update();
        dxwnd.shutdown();

    }



}
   

#endif

#if 0

model loading


/*view = glm::mat4(cam.getViewMatrix());

loading.Win32useShader();

loading.setMat4("projection", projection);
loading.setMat4("view", view);

glm::mat4 modelNanosuit = glm::mat4(1.0f);
modelNanosuit = glm::translate(modelNanosuit, glm::vec3(5.0f, -1.0f, 0.0f));
modelNanosuit = glm::scale(modelNanosuit, glm::vec3(0.2f, 0.2f, 0.2f));
loading.setMat4("model", modelNanosuit);
secondmodel.drawMesh(&loading);

modelNanosuit = glm::mat4(1.0f);
modelNanosuit = glm::translate(modelNanosuit, glm::vec3(10.0f, -1.0f, 0.0f));
modelNanosuit = glm::scale(modelNanosuit, glm::vec3(0.2f, 0.2f, 0.2f));
loading.setMat4("model", modelNanosuit);
firstmodel.drawMesh(&loading);

modelNanosuit = glm::mat4(1.0f);
modelNanosuit = glm::translate(modelNanosuit, glm::vec3(-10.0f, -1.0f, 0.0f));
modelNanosuit = glm::scale(modelNanosuit, glm::vec3(0.2f, 0.2f, 0.2f));
loading.setMat4("model", modelNanosuit);
cityModel.drawMesh(&loading);


dispShader.Win32useShader();
dispShader.setMat4("projection", projection);
dispShader.setMat4("view", view);

glm::mat4 model = glm::mat4(1.0f);
model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
dispShader.setMat4("model", model);
dispShader.setVec3("viewPos", cam.getCamPos());
dispShader.setVec3("lightPos", lightPos);
dispShader.setFloat("heightScale", 0.1f);

bindTexture2D(0, diffuseMapForNormals);
bindTexture2D(1, normalMap);
bindTexture2D(2, dispMap);

renderQuad();


model = glm::mat4(1.0f);
model = glm::translate(model, lightPos);
model = glm::scale(model, glm::vec3(0.1f));
dispShader.setMat4("model", model);
renderQuad();

floorShader.Win32useShader();

floorShader.setMat4("projection", projection);
floorShader.setMat4("view", view);

floorShader.setVec3("viewPos", cam.camPos);
floorShader.setVec3("lightPos", lightposfloor);

renderQuad();
*/
//sky.renderSkybox(&cubeMap, &cam, view, projection, cubemaptexture);




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


void renderScene(Shader *shader, unsigned int &vao)
{
    glm::mat4 model = glm::mat4(1.0f);
    shader->setMat4("model", model);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // cubes
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->setMat4("model", model);
    renderCube();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->setMat4("model", model);
    renderCube();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
    model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(0.25));
    shader->setMat4("model", model);
    renderCube();
}

#endif


