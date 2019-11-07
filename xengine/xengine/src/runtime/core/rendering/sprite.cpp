#include "sprite.h"


namespace XEngine
{
    namespace Rendering
    {
        Sprite::Sprite(float x, float y, float w, float h, glm::vec4 & color, Shader & shader) :
            Renderable2d(glm::vec3(x, y, 0), glm::vec2(w, h), color), mShader(shader)
        {

            GLfloat vert[] =
            {
                0, 0, 0,
                0, h, 0,
                w, h, 0,
                w, 0, 0
            };

            GLfloat colors[] =
            {
                color.x, color.y, color.z, color.w,
                color.x, color.y, color.z, color.w,
                color.x, color.y, color.z, color.w,
                color.x, color.y, color.z, color.w,
            };

            GLuint ind[] =
            {
                0, 1, 2,
                2, 3, 0
            };

            mvertexArray = new VertexArray();
            mindexBuffer = new IndexBuffer(ind, 6);

            mvertexArray->addBuffer(new VertexBuffer(vert, 4 * 3, 3), 0);
            mvertexArray->addBuffer(new VertexBuffer(colors, 4 * 4, 4), 1);

        }

        Sprite::~Sprite()
        {
            delete mvertexArray;
            delete mindexBuffer;            
        }

    }
}