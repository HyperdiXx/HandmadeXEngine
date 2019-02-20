#include "text.h"


namespace XEngine
{
    /*void InitSnt(uint32 &VAO, uint32 &VBO)
    {
        FT_Library ft;
        FT_Face face;

        if (FT_Init_FreeType(&ft))
            std::cout << "Failed to init FONT LIB\n";
        if (FT_New_Face(ft, "src/fonts/arial.ttf", 0, &face))
            std::cout << "Failed to load font\n";
        FT_Set_Pixel_Sizes(face, 0, 48);


        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (GLbyte ch = 0; ch < 128; ++ch)
        {
            if (FT_Load_Char(face, ch, FT_LOAD_RENDER))
            {
                std::cout << "Error::Loading chars\n";
                continue;
            }

            GLuint texture;

            glGenTextures(1, &texture);
            glBindTexture(TEXTURE2D, texture);

            glTexImage2D(TEXTURE2D, 0,
                RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer);

            glTexParameteri(TEXTURE2D, WRAP_S, CLAMP_EDGE);
            glTexParameteri(TEXTURE2D, WRAP_T, CLAMP_EDGE);
            glTexParameteri(TEXTURE2D, MIN_FILTER, LINEAR);
            glTexParameteri(TEXTURE2D, MAG_FILTER, LINEAR);

            Letter l = { texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                                  glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                                  face->glyph->advance.x };
            Characters.insert(std::pair<GLchar, Letter>(ch, l));
        }

        glBindTexture(GL_TEXTURE_2D, 0);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        
    }

    void RenderSmth(Shader &shader, uint32 &VAO, uint32 &VBO, std::string text, glm::vec3 color, uint32 x, uint32 y, uint32 scale)
    {
        Win32UseShader(&shader);
        setVec3(&shader, "color", color);

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        for(std::string::iterator i = text.begin(); i != text.end(); ++i)
        {
            Letter l = Characters[*i];

            real32 xpos = x + l.Bearing.x * scale;
            real32 ypos = y - (l.Size.y - l.Bearing.y) * scale;
            
            real32 w = l.Size.x * scale;
            real32 h = l.Size.y * scale;

            real32 vertices[6][4] = {
                {xpos,      ypos + h,   0.0, 0.0},
                {xpos,      ypos,       0.0, 1.0},
                {xpos + w,  ypos,       1.0, 1.0},
                {xpos,      ypos + h,   0.0, 0.0},
                {xpos + w,  ypos,       1.0, 1.0},
                {xpos + w,  ypos + h,   1.0, 0.0}
            };

            glBindTexture(TEXTURE2D, l.id);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDrawArrays(GL_TRIANGLES, 0, 6);
            x += (l.Advance >> 6) * scale;


        }

        glBindVertexArray(0);
        glBindTexture(TEXTURE2D, 0);
    }

    */
}
