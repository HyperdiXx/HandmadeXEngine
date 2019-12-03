#include "layer.h"

namespace XEngine
{
    namespace Rendering
    {
        Layer::Layer(Render2d* render, Shader* shader, glm::mat4 mat) : mRender(render), mShader(shader), mprojMat(mat)
        {
            mShader->bind();
            mShader->setMat4("projection", mprojMat);
            mShader->unbind();
        }

        Layer::~Layer()
        {
            delete mRender;
            delete mShader;
            for (int i = 0; i < mRenderables.size(); ++i)
            {
                delete mRenderables[i];
            }
        }

        void Layer::add(Renderable2d* obj)
        {
            mRenderables.push_back(obj);
        }

        void Layer::render()
        {
            mShader->bind();
            mShader->setMat4("projection", mprojMat);

            //for (const Renderable2d* renderableObj : mRenderables)
            //    mRender->submit(renderableObj);

            //mRender->add();

            mShader->unbind();
        }
    }
}