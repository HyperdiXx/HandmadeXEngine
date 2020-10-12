
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_PARAMETER_TAGS_H
#include FT_MODULE_H

int main()
{
    char *font_name = "arial.ttf";

    FT_Library lib = {};
    FT_Face face = {};

    if (FT_Init_FreeType(&lib))
    {
        //print_error("FREETYPE: Couldnt init free type lib");
    }

    if (FT_New_Face(lib, font_name, 0, &face))
    {
        //print_error("FREETYPE: Failed to load font");
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    return 0;
}
