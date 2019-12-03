#include "glrenderapi.h"

#include "opengl.h"

namespace XEngine
{
    namespace Rendering
    {
        void OpenGLRenderAPI::init()
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            // TODO: place on render command 
            glEnable(GL_DEPTH_TEST);
        }

        void OpenGLRenderAPI::setViewport(int32 x, int32 y, int32 width, int32 height)
        {
            glViewport(x, y, width, height);
        }

        void OpenGLRenderAPI::clear()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void OpenGLRenderAPI::clearColor(real32 r, real32 g, real32 b, real32 a)
        {
            glClearColor(r, g, b, a);
        }
    }
}



