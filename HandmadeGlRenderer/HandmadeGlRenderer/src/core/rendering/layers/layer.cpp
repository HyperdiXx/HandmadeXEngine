#include "layer.h"

namespace XEngine
{
    namespace Rendering
    {
        Layer::Layer(Renderer2d* render, Shader* shader, glm::mat4 mat) : mRender(render), mShader(shader), mprojMat(mat)
        {
            mShader->enableShader();
            mShader->setMat4("projection", mprojMat);
            mShader->disableShader();
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
            mShader->enableShader();
            mShader->setMat4("projection", mprojMat);

            for (const Renderable2d* renderableObj : mRenderables)
                mRender->submit(renderableObj);

            mRender->flush();

            mShader->disableShader();
        }
    }
}