#include "sprite.h"


namespace XEngine
{
    namespace Rendering
    {
        Sprite::Sprite(float x, float y, float w, float h, vec4f & color, Shader & shader) :
            Renderable2d(vec3f(x, y, 0), vec2f(w, h), color), mShader(shader)
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

            //mVertexArray = new VertexArray();
            //mIndexBuffer = new IndexBuffer(ind, 6);

            //mvertexArray->addBuffer(new VertexBuffer(vert, 4 * 3, 3), 0);
            //mvertexArray->addBuffer(new VertexBuffer(colors, 4 * 4, 4), 1);

        }

        Sprite::~Sprite()
        {
            delete mVertexArray;
            delete mIndexBuffer;            
        }

    }
}