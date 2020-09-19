#ifndef APP_CPP
#define APP_CPP

#include "xe_common.h"
#include "app_state.h"
#include "xe_parser.h"
#include "xe_containers.h"

#include "xe_string.cpp"
#include "xe_parser.cpp"
#include "xe_containers.cpp"

APP_LOAD_DATA
{
    int a = 10;
    int c = a * 10 + 5;
    //p_state = ps;
    //LoadAllOpenGLProcedures();
}

APP_UPDATE
{
    //glClearColor(1, 0, 0, 1);
    //glClear(GL_COLOR_BUFFER_BIT);
    //os->RefreshScreen();
}

#endif