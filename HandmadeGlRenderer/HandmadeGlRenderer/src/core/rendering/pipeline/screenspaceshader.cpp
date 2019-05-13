#include "screenspaceshader.h"

XEngine::Rendering::ScreenSpaceShader::ScreenSpaceShader(const char * fragmentPath)
{
    initializeQuad();
    //shad = new Shader("shaders/screen.vert", fragmentPath);
    shad = new Shader("ScreenQuad_" + getShaderName(fragmentPath));

    shad->addShader("");
    shad->addShader("");
    shad->linkPrograms();
}

void XEngine::Rendering::ScreenSpaceShader::draw()
{
    drawQuad();
}

void XEngine::Rendering::ScreenSpaceShader::drawQuad()
{
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void XEngine::Rendering::ScreenSpaceShader::initializeQuad()
{
    if (!initialized) 
    {
        float vertices[] =
        {
            -1.0f, -1.0f, 0.0, 0.0,
            1.0f, -1.0f, 1.0, 0.0,
            -1.0f,  1.0f, 0.0, 1.0,
            1.0f,  1.0f, 1.0, 1.0,
            -1.0f,  1.0f, 0.0, 1.0,
            1.0f, -1.0f, 1.0, 0.0
        };

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        ScreenSpaceShader::initialized = true;
}
