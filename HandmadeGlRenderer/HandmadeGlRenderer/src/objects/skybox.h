#pragma once

#ifndef SKYBOXH
#define SKYBOXH

#include "src/core/rendering/pipeline/shader.h"
#include "src/core/rendering/openglnew/vao.h"
#include "../core/rendering/openglnew/vertexarray.h"
#include "../core/rendering/openglnew/buffer.h"
#include "src/core/cameras/camera.h"


namespace XEngine
{
    namespace Rendering
    {
        class Skybox
        {
        public:
            Skybox()
            {
                sky = (GeometryBuffer*)malloc(sizeof(GeometryBuffer));
            }

            Skybox(Shader *skyshader)
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

            };
            ~Skybox()
            {
                delete VAO;
                free(sky);
            }

            void createSkybox();
            void renderSkybox(Shader * shader, XEngine::Camera *cam, glm::mat4& v, glm::mat4& proj, uint32& tex);
            GeometryBuffer* getGeometryBuffer() { return sky; };
        private:
            GeometryBuffer *sky;
            VertexArray *VAO;
            VertexBuffer *VBO;
        };


    }
}

#endif // !SKYBOX

