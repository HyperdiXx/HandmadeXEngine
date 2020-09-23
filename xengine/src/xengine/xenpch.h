#pragma once

#ifndef UTILITYH
#define UTILITYH

#ifdef _WIN32
    #define APIENTRY __stdcall

#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#endif 

#define WINDOWWIDTH 1280
#define WINDOWHEIGHT 720

#ifndef MATHGLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif // !MATHGLM




#endif // !UTILITYH

