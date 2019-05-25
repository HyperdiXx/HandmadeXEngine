#pragma once

#ifndef SKYBOXH
#define SKYBOXH

#include "src/core/rendering/pipeline/shader.h"
#include "src/core/rendering/openglnew/vao.h"
#include "../core/rendering/api/opengl/vertexarray.h"
#include "../core/rendering/api/opengl/buffer.h"
#include "../core/rendering/texture.h"
#include "../core/rendering/api/opengl/glframebuffer.h"
#include "../core/rendering/pipeline/screenspaceshader.h"


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
            
            GeometryBuffer* getGeometryBuffer() { return sky; };
        private:
            GeometryBuffer *sky;
            VertexArray *VAO;
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
            
            ScreenSpaceShader * skyboxShader;
            Rendering::GLFrameBuffer * skyboxFBO;

            colorPreset presetSunset, highSunPreset;
            glm::vec3 skyColorTop, skyColorBottom;

        };
    }
}

#endif // !SKYBOX

