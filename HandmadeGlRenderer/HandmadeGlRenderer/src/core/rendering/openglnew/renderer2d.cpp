#include "renderer2d.h"



namespace XEngine
{
    namespace Rendering
    {
        void Renderer2d::submit(const Renderable2d* renderObj)
        {
            mrenderQ.push_back(renderObj);
        }

        void Renderer2d::flush()
        {
            glm::mat4 model = glm::mat4(1.0f);
            const Renderable2d* objToRender = mrenderQ.front();
            objToRender->getVAO()->bind();
            objToRender->getIBO()->bind();
            model = glm::translate(model, objToRender->getPos());
            objToRender->getShader().setMat4("model", model);
            glDrawElements(GL_TRIANGLES, objToRender->getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);
            objToRender->getVAO()->unbind();
            objToRender->getIBO()->unbind();
            mrenderQ.pop_front();
        }

    }

}