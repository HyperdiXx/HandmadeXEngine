#pragma once

#include "../openglnew/renderer2d.h"
#include "../openglnew/irenderable2d.h"

namespace XEngine
{
    namespace Rendering
    {
        class Layer
        {
        protected:
            Layer(Renderer2d* render, Shader* shader, glm::mat4 mat);
        public:
            Layer()
            {

            }
            virtual ~Layer();

            virtual void add(Renderable2d *obj);
            virtual void render();



        protected:
            std::vector<Renderable2d*> mRenderables;
            Renderer2d* mRender;
            Shader* mShader;
            glm::mat4 mprojMat;
        };
    }
}


