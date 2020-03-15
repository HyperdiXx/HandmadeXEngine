#pragma once

#ifndef UTILITYH
#define UTILITYH

#include <ft2build.h>
#include FT_FREETYPE_H  
#define GLEW_STATIC

#ifdef _WIN32
    #define APIENTRY __stdcall
#endif

#include <utility>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>

#define WINDOWWIDTH 1280
#define WINDOWHEIGHT 720

#if defined _WIN64




#endif


#ifndef MATHGLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif // !MATHGLM




#endif // !UTILITYH

