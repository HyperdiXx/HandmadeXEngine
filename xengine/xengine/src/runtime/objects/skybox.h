#pragma once

#ifndef SKYBOXH
#define SKYBOXH

#include <runtime/core/rendering/api/base/shader.h>
#include <runtime/core/rendering/api/base/vertexarray.h>
#include <runtime/core/rendering/api/base/vertexbuffer.h>
#include <runtime/core/rendering/texture.h>
#include <runtime/core/rendering/api/opengl/glframebuffer.h>

namespace XEngine
{
    namespace Rendering
    {
        class Skybox
        {
        public:
            Skybox();
            Skybox(Shader *skyshader);
            ~Skybox();


            void createSkybox();
            void renderSkybox(Shader * shader, glm::mat4& v, glm::mat4& proj);
            
           
        private:
            //VertexArray *VAO;
            VertexBuffer *VBO;
            Cubemap *tex;
            XEngine::Cubemap cub;
            std::vector<std::string> mtextures;
            unsigned int cubemaptexture;
        };

        struct colorPreset
        {
            glm::vec3 cloudColorBottom, skyColorTop, skyColorBottom, lightColor, fogColor;
        };

        class SkyboxProced
        {
        public:

            SkyboxProced();
            ~SkyboxProced();

            void draw();
            void update();

            colorPreset DefaultPreset();
            colorPreset SunsetPreset();
            colorPreset SunsetPreset1();

            void mixSkyColorPreset(float v, colorPreset p1, colorPreset p2);

            unsigned int getSkyTexture() 
            {
                return skyboxFBO->getColorTexture();
            }
        private:
            
            
            Rendering::GLFrameBuffer * skyboxFBO;

            //colorPreset presetSunset, highSunPreset;
            glm::vec3 skyColorTop, skyColorBottom;

        };
    }
}

#endif // !SKYBOX

