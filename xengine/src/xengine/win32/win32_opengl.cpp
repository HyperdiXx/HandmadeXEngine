
global HGLRC graphics_context;

PFNWGLCHOOSEPIXELFORMATARBPROC    wglChoosePixelFormatARB;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
PFNWGLMAKECONTEXTCURRENTARBPROC   wglMakeContextCurrentARB;
PFNWGLSWAPINTERVALEXTPROC         wglSwapIntervalEXT;

internal void* Win32LoadOpenglProcedure(char *name)
{
    void *ptr = (void *)wglGetProcAddress(name);
    
    if (ptr == 0 || (ptr == (void*)0x1) || (ptr == (void*)0x2) || (ptr == (void*)0x3) || (ptr == (void*)-1))
    {
        HMODULE moduleLib = LoadLibraryA("opengl32.dll");
        ptr = (void *)GetProcAddress(moduleLib, name);
    }

    return ptr;
}

internal void Win32GetWglExtFunctions()
{
    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)Win32LoadOpenglProcedure("wglChoosePixelFormatARB");
    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)Win32LoadOpenglProcedure("wglCreateContextAttribsARB");
    wglMakeContextCurrentARB = (PFNWGLMAKECONTEXTCURRENTARBPROC)Win32LoadOpenglProcedure("wglMakeContextCurrentARB");
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)Win32LoadOpenglProcedure("wglSwapIntervalEXT");
}

internal bool Win32InitGraphicsDevice(HDC *device_context, HINSTANCE h_inst)
{
    bool result = 0;

    // GL Context for loading external functions
    int pixel_format = 0;
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    pixel_format = ChoosePixelFormat(*device_context, &pfd);

    if (pixel_format)
    {
        SetPixelFormat(*device_context, pixel_format, &pfd);
        HGLRC gl_dummy_render_context = wglCreateContext(*device_context);
        wglMakeCurrent(*device_context, gl_dummy_render_context);

        Win32GetWglExtFunctions();
       
        {
            int pf_attribs_i[] =
            {
                WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
                WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
                WGL_COLOR_BITS_ARB, 32,
                WGL_DEPTH_BITS_ARB, 24,
                WGL_STENCIL_BITS_ARB, 8,
                0
            };

            UINT num_formats = 0;
            wglChoosePixelFormatARB(*device_context,
                pf_attribs_i,
                0,
                1,
                &pixel_format,
                &num_formats);
        }

        if (pixel_format)
        {
            const int context_attribs[] =
            {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                WGL_CONTEXT_MINOR_VERSION_ARB, 3,
                0
            };

            graphics_context = wglCreateContextAttribsARB(*device_context,
                                           gl_dummy_render_context,
                                           context_attribs);
           
            if (graphics_context)
            {
                wglMakeCurrent(*device_context, 0);
                wglDeleteContext(gl_dummy_render_context);
                wglMakeCurrent(*device_context, graphics_context);
                wglSwapIntervalEXT(0);
                result = true;
            }
        }
    }

    return result;
}

internal void Win32DestroyGraphicsContext(HDC *device_context)
{
    wglMakeCurrent(*device_context, 0);
    wglDeleteContext(graphics_context);
}
