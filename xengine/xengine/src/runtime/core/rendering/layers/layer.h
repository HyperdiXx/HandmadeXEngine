#pragma once

#include "../render/render2d.h"
#include "../render/renderable2d.h"

namespace XEngine
{
    namespace Rendering
    {
        class Layer
        {
        protected:
            Layer(Render2d* render, Shader* shader, glm::mat4 mat);
        public:
            Layer()
            {

            }
            virtual ~Layer();

            virtual void add(Renderable2d *obj);
            virtual void render();



        protected:
            std::vector<Renderable2d*> mRenderables;
            Render2d* mRender;
            Shader* mShader;
            glm::mat4 mprojMat;
        };
    }
}


