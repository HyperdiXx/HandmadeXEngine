#pragma once

#ifndef GLTEXTURE2D_H
#define GLTEXTURE2D_H

#include <runtime/core/rendering/api/base/texture2d.h>

#include "opengl.h"

namespace XEngine
{
    namespace Rendering
    {
        class GLTexture2D : public Texture2D
        {
        public:
            GLTexture2D(const char* path);
            virtual ~GLTexture2D();

            virtual void fillData(void* data, uint32 size) override;
            virtual void bind() const override;

            virtual uint32 getWidth() const override { return m_width; };
            virtual uint32 getHeight() const override { return m_height; };

            

        private:
            const char* m_path;
            uint32 m_width;
            uint32 m_height;
            uint32 m_id;
            GLenum m_internalFormat;
            GLenum m_dataFormat;
        };
    }
}
#endif // !GLTEXTURE2D_H

