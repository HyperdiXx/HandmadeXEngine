#include "render2d.h"



namespace XEngine
{
    namespace Rendering
    {
        /*void Render2d::submit(const Renderable2d* renderObj)
        {
           mrenderQ.push_back((Sprite*)renderObj);
        }

        void Render2d::flush()
        {
            while (!mrenderQ.empty())
            {
                mat4 model = mat4::identity();
                const Sprite* objToRender = mrenderQ.front();
                objToRender->getVAO()->bind();
                objToRender->getIBO()->bind();
                model = mat4::translate(objToRender->getPos());
                objToRender->getShader().setMat4("model", model);
                glDrawElements(GL_TRIANGLES, objToRender->getIBO()->getCount(), GL_UNSIGNED_INT, 0);
                objToRender->getIBO()->unbind();
                objToRender->getVAO()->unbind();
                mrenderQ.pop_front();
            }

        }*/

    }

}