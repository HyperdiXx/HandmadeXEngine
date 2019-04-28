#include "skybox.h"


using namespace XEngine;
using namespace Rendering;


XEngine::Rendering::Skybox::Skybox()
{
    sky = (GeometryBuffer*)malloc(sizeof(GeometryBuffer));
    tex = new Texture2D(mtextures);
}

XEngine::Rendering::Skybox::Skybox(Shader * skyshader)
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
}

XEngine::Rendering::Skybox::~Skybox()
{
    
        glDeleteVertexArrays(1, &sky->vao);
        glDeleteBuffers(1, &sky->vbo);
        free(sky);
        delete(tex);
    
}

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


    mtextures.push_back("src/textures/right.jpg");
    mtextures.push_back("src/textures/left.jpg");
    mtextures.push_back("src/textures/top.jpg");
    mtextures.push_back("src/textures/bottom.jpg");
    mtextures.push_back("src/textures/front.jpg");
    mtextures.push_back("src/textures/back.jpg");

    
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

    cubemaptexture = tex->loadTextureCubemap(mtextures);

}


void Skybox::renderSkybox(Shader *shader, glm::mat4& v, glm::mat4& proj)
{
    tex->setDepthFunc(GL_LEQUAL);
    shader->enableShader();
    v = glm::mat3(v);
    shader->setMat4("projection", proj);
    shader->setMat4("view", v);
    glBindVertexArray(sky->vao);
    tex->bindCubeTexture2D(0, cubemaptexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    tex->setDepthFunc(GL_LESS);
}





