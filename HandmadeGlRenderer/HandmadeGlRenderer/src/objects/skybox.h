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


    }
}

#endif // !SKYBOX

