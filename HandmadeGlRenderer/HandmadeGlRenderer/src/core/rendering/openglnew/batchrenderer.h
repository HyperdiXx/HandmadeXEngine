#pragma once

#include <deque>
#include "buffer.h"
#include "render2d.h"


namespace XEngine
{
    namespace Rendering
    {

#define RENDER_MAX_SPRITES 10000
#define RENDER_VERTEX_SIZE sizeof(Vertex)
#define RENDER_SPRITE_SIZE RENDER_VERTEX_SIZE * 4
#define RENDER_BUFFER_SIZE RENDER_SPRITE_SIZE * RENDER_MAX_SPRITES
#define RENDER_INDICES_SIZE RENDER_MAX_SPRITES * 6

        class BatchRenderer2d : public Render2d
        {
        public:
            BatchRenderer2d()
            {

            }

            ~BatchRenderer2d()
            {
                delete mIBO;
                glDeleteBuffers(1, &mVBO);

            }
                
            void submit(const Renderable2d* renderObj) override;
            void flush() override;
        private:
            void init();
        private:
            IndexBuffer* mIBO;
            GLuint mVAO;
            GLuint mVBO;
            GLsizei mIndCount;
            
        };
                                   
    }

}