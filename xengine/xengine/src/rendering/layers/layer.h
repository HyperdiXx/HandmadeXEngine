#pragma once

#include <rendering/render/render.h>
#include <rendering/render/renderable2d.h>

namespace XEngine
{
    namespace Rendering
    {
        class Layer
        {
        protected:
            Layer(Render* render, Shader* shader, glm::mat4 mat);
        public:
            Layer() {}
            
            virtual ~Layer();

            virtual void add(Renderable2d *obj);
            virtual void render();



        protected:
            std::vector<Renderable2d*> mRenderables;
            Render* mRender;
            Shader* mShader;
            glm::mat4 mprojMat;
        };
    }
}


