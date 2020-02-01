#pragma once

#include <rendering/api/base/shader.h>
#include <rendering/api/opengl/opengl.h>

namespace XEngine
{
    namespace Rendering
    {
        class ShadowMap
        {
        public:
            ShadowMap(int w, int h) 
            {
                init(w, h);
                //shadows = new Shader("src/shaders/basicshadows.vs", "src/shaders/basicshadows.fs");
                //depthShader = new Shader("src/shaders/lightrender.vs", "src/shaders/lightrender.fs");
            };
            ~ShadowMap()
            {
                //delete shadows;
                //delete depthShader;
            }

            void bind();
            void unbind();

            void createShadows();
            void init(int w, int h);
            void calculateMatrix();
            void setShader();
            void setShaderDepth(glm::mat4 projectiom, glm::mat4 view, glm::vec3 &pos, glm::vec3 lightPos, glm::mat4 &mat);
            void updateShadows(glm::vec3 lightPos);


        private:
            //GLFrameBuffer *fb;
            //Shader *shadows;
            //Shader *depthShader;
            unsigned int depthMapFrame;
            unsigned int depthMap;
        };
    }
}