#pragma once

#ifndef SKYBOXH
#define SKYBOXH

#include "src/core/rendering/pipeline/shader.h"
#include "src/core/rendering/openglnew/vao.h"
#include "../core/rendering/api/opengl/vertexarray.h"
#include "../core/rendering/api/opengl/buffer.h"
#include "../core/rendering/texture.h"


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
                tex = new Texture2D(cub.textures);
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
                glDeleteVertexArrays(1, &sky->vao);
                glDeleteBuffers(1, &sky->vbo);
                free(sky);
                delete(tex);
            }

            void createSkybox();
            void renderSkybox(Shader * shader, glm::mat4& v, glm::mat4& proj);
            GeometryBuffer* getGeometryBuffer() { return sky; };
        private:
            GeometryBuffer *sky;
            VertexArray *VAO;
            VertexBuffer *VBO;
            Texture2D *tex;
            XEngine::Cubemap cub;
            unsigned int cubemaptexture;
        };


    }
}

#endif // !SKYBOX

