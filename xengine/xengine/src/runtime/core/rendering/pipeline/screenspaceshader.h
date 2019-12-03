#pragma once

#include <runtime/core/rendering/api/base/shader.h>

namespace XEngine
{
    namespace Rendering
    {
         class ScreenSpaceShader
         {
         public:
             ScreenSpaceShader(const char * fragmentPath);
             ~ScreenSpaceShader() {}

             Shader * const getShaderPtr()
             {
                 return shad;
             }

             Shader & const getShader()
             {
                 return *shad;
             }

             void draw();
             static void drawQuad();

             static void disableTests()
             {
                 //glDisable(GL_CLIP_DISTANCE0);
                 glDisable(GL_DEPTH_TEST);
             }

             static void enableTests()
             {
                 glEnable(GL_DEPTH_TEST);
             }

         private:
             Shader *shad;
             //static unsigned int quadVAOSpace, quadVBOSpace;
             //static bool initialized;

             void initializeQuad();
         };
     }
    
}