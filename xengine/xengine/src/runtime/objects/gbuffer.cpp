#include "gbuffer.h"

XEngine::Rendering::Gbuffer::Gbuffer()
{
  
}

XEngine::Rendering::Gbuffer::~Gbuffer()
{
    

}

void XEngine::Rendering::Gbuffer::init()
{
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBuffer);

    glBindTexture(GL_TEXTURE_2D, gPos);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WINDOWWIDTH, WINDOWHEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPos, 0);

    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WINDOWWIDTH, WINDOWHEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

    glGenTextures(1, &gColor);
    glBindTexture(GL_TEXTURE_2D, gColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOWWIDTH, WINDOWHEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gColor, 0);

    glGenTextures(1, &gDepth);
    glBindTexture(GL_TEXTURE_2D, gDepth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, WINDOWWIDTH, WINDOWHEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, gDepth, 0);

    unsigned int drawBuffers[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    //glDrawBuffers(ARRAYSIZE(drawBuffers), drawBuffers);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);




}
