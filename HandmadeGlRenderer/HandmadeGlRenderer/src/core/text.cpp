#include "text.h"


namespace XEngine
{
    void InitSnt()
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


    }
}
