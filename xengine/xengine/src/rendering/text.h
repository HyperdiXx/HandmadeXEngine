#pragma once

#ifndef TEXTH
#define TEXTH

#include <xenpch.h>

#include "texture.h"
#include <rendering/api/base/shader.h>

namespace ftgl {
    struct texture_atlas_t;
    struct texture_font_t;
}

namespace XEngine
{
    namespace Rendering
    {
        
        class Font 
        {
        public:
            Font(const char* path, Shader *shader);

            ~Font()
            {
                
            }

            void add();

            inline void SetScale(const glm::vec2& scale) { mscale = scale; }
            inline const glm::vec2& GetScale() const { return mscale; }

            inline const std::string& GetName() const { return mname; }
            inline const std::string& GetFileName() const { return mfilename; }
            inline float GetFontSize() const { return msize; }

            glm::vec2 GetOffsets(const std::string& text) const;
            float GetWidth(const std::string& text) const;
            float GetHeight(const std::string& text) const;
            glm::vec2 GetSize(const std::string& text) const;

            void updateText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) const;

        private:

            void initFreeType();

            struct Character {
                GLuint     textureID;  
                glm::ivec2 Size;       
                glm::ivec2 Bearing;    
                GLuint     Advance;    
            };

            std::map<GLchar, Character> Characters;

        private:

            //ftgl::texture_atlas_t *mftAtlas;
            //ftgl::texture_font_t *mftFont;
            glm::vec2 mscale;
            std::string mname;
            std::string mfilename;
            float msize;
            GLuint texture;
            Shader* mshader;
            GLuint VAO, VBO;
        };
    }

}

#endif
