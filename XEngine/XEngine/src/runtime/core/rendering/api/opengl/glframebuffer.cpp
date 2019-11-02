#include "glframebuffer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <xenpch.h>

namespace XEngine
{
    namespace Rendering
    {
        GLFrameBuffer::GLFrameBuffer(int w, int h) : width(w), height(h)
        {
        }

        GLFrameBuffer::~GLFrameBuffer()
        {
            glDeleteFramebuffers(1, &fbo);
            glDeleteRenderbuffers(1, &depthTexture);
            glDeleteTextures(1, &colorTexture);
        }


        void GLFrameBuffer::init()
        {
            glGenFramebuffers(1, &fbo);
            bind();

            glGenTextures(1, &colorTexture);
            glBindTexture(GL_TEXTURE_2D, colorTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOWWIDTH, WINDOWHEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

            glGenRenderbuffers(1, &depthTexture);
            glBindRenderbuffer(GL_RENDERBUFFER, depthTexture);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WINDOWWIDTH, WINDOWHEIGHT);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthTexture);
                        
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Framebuffer not complete!" << std::endl;
            unbind();
        }

        void GLFrameBuffer::bind() const
        {
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        }

        void GLFrameBuffer::unbind() const
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    
        void GLFrameBuffer::blitFramebuffer()
        {
            glBlitFramebuffer(0, 0, WINDOWWIDTH, WINDOWHEIGHT, 0, 0, WINDOWWIDTH, WINDOWHEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        }

        void GLFrameBuffer::clear()
        {
            glDeleteFramebuffers(1, &fbo);
            glDeleteRenderbuffers(1, &depthTexture);
            glDeleteTextures(1, &colorTexture);
        }
    }
}



