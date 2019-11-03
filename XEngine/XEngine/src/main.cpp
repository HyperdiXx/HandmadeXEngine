
/*
    XEngine.
    OpenGL API 4.5
    DX11

    Features: Camera, ImGUI, Textures, MultiTextures, Lighting, Redering Interfaces, FrameBuffers, Cubemap, MSAA, ForwardShading, DefferedShading, Stencil, Blending, PostProcess,
    FaceCulling, Instancing, DynamicShadowMapping + DirLight, OmniLightsShadows, NormalMapping, ParallaxMapping,  Antialiasing, Gamma Correctiom
    TODO(vlad): Assimp, Logger, 
        
        
        Bloom,
        HDR, SSAO, PBR, IBL
        Spray Particles, Skinning

        SceneManager, Stack Linked List

        DX11 ...
        DX12 ...


        Scene 1: Objects, plane, shadows, Dynamic dirLight, Spray Particles
        Scene 2: PBR, IBL
        Scene 3: Sky, Volumetric clouds, terrain

*/

#include <iostream>


#define OPENGL
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <xenpch.h>
#include <math/xemath.h>


#define internal static

void 
framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

internal void 
initGLFW(int32 version)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
}

internal 
void initShader()
{

}

internal GLFWwindow* 
createWindow(const char* name)
{
    GLFWwindow* res = glfwCreateWindow(1280, 720, name, NULL, NULL);
    
    if (res == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(res);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }
    glfwSetFramebufferSizeCallback(res, framebufferSizeCallback);
    glfwSwapInterval(1);
    
    return res;
}

int CALLBACK
WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR lp_cmd_line, int n_show_cmd)
{
    /*using namespace XEngine;

    Application *testapp = (Application*)malloc(sizeof(Application));
#ifdef  OPENGL
    testapp->OpenGLScene5();
#else
    testapp->DX11InitEngine();
#endif

    free(testapp);*/

    vec2f test;
    mat4 matrix(1.0f);
 
    float r = test.length();
    
    initGLFW(3);

    GLFWwindow* m_window = createWindow("Game");

    while (!glfwWindowShouldClose(m_window))
    {
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    glfwTerminate();

    return (0);
}