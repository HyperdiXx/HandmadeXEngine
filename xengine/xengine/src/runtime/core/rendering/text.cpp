#include "text.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <freetype/freetype.h>

namespace XEngine
{
    namespace Rendering
    {
        Font::Font(const char* path, Shader *shader) :
             mfilename(path), mshader(shader)
        {
            FT_Library lib;

            if (FT_Init_FreeType(&lib))
                printf("Error. Could not init font lib!!!\n");

            FT_Face face;

            if (FT_New_Face(lib, path, 0, &face))
                printf("Error. Couldnt init font");

            FT_Set_Pixel_Sizes(face, 0, 48);

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            for (int c = 0; c < 128; ++c)
            {
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {

                }

                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                Character character =
                {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    face->glyph->advance.x
                };

                Characters.insert(std::pair<GLchar, Character>(c, character));
            }

            glBindTexture(GL_TEXTURE_2D, 0);
            FT_Done_Face(face);
            FT_Done_FreeType(lib);

            
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            
            glm::mat4 orho = glm::mat4(1.0f);

            orho = glm::ortho(0.0f, float(WINDOWWIDTH), 0.0f, float(WINDOWHEIGHT), -1.0f, 1.0f);


            shader->enableShader();
            shader->setMat4("projection", orho);

        }

        void Font::updateText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) const
        {
                
                mshader->enableShader();
                mshader->setVec3("color", color);
                glActiveTexture(GL_TEXTURE0);
                glBindVertexArray(VAO);

                
                std::string::const_iterator c;
                for (c = text.begin(); c != text.end(); c++)
                {
                    Character ch = Characters.at(*c);

                    GLfloat xpos = x + ch.Bearing.x * scale;
                    GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

                    GLfloat w = ch.Size.x * scale;
                    GLfloat h = ch.Size.y * scale;
                    

                    GLfloat vertices[6][4] = {
                        { xpos,     ypos + h,   0.0, 0.0 },
                        { xpos,     ypos,       0.0, 1.0 },
                        { xpos + w, ypos,       1.0, 1.0 },

                        { xpos,     ypos + h,   0.0, 0.0 },
                        { xpos + w, ypos,       1.0, 1.0 },
                        { xpos + w, ypos + h,   1.0, 0.0 }
                    };
                  
                    glBindTexture(GL_TEXTURE_2D, ch.textureID);

                    glBindBuffer(GL_ARRAY_BUFFER, VBO);
                    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                    
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                    
                    x += (ch.Advance >> 6) * scale; 
                }
                glBindVertexArray(0);
                glBindTexture(GL_TEXTURE_2D, 0);
            
        }
    }
}
