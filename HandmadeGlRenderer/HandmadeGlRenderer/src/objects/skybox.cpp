#include "skybox.h"

#include "../core/systems/textureload.h"

using namespace XEngine;
using namespace Rendering;


void Skybox::createSkybox()
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

    
    

    cub.textures.push_back("src/textures/right.jpg");
    cub.textures.push_back("src/textures/left.jpg");
    cub.textures.push_back("src/textures/top.jpg");
    cub.textures.push_back("src/textures/bottom.jpg");
    cub.textures.push_back("src/textures/front.jpg");
    cub.textures.push_back("src/textures/back.jpg");

    
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    sky->vao = skyboxVAO;
    sky->vbo = skyboxVBO;

    cubemaptexture = XEngine::Utils::loadCubemap(cub.textures);

}


void Skybox::renderSkybox(Shader *shader, glm::mat4& v, glm::mat4& proj)
{
    Texture2d::setDepthFunc(GL_LEQUAL);
    shader->enableShader();
    v = glm::mat3(v);
    shader->setMat4("projection", proj);
    shader->setMat4("view", v);
    glBindVertexArray(sky->vao);
    Texture2d::bindCubeTexture2D(0, cubemaptexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    Texture2d::setDepthFunc(GL_LESS);
}





