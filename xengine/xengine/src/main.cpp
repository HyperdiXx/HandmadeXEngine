
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

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <math/xemath.h>
#include <runtime/application/testapp.h>
#include <runtime/application/test.h>
#include <runtime/core/rendering/api/base/shader.h>
#include <runtime/core/rendering/api/base/texture2d.h>
#include <runtime/core/rendering/api/base/vertexbuffer.h>
#include <runtime/core/rendering/api/base/indexbuffer.h>
#include <runtime/core/rendering/api/base/vertexarray.h>

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
    initGLFW(3);

    GLFWwindow* window = createWindow("XEngine");

    using namespace XEngine::Rendering;
    
    Shader *triangleShader = Shader::create("shaders/simple2d.vs", "shaders/simple2d.fs");

    Texture2D *texture = Texture2D::create("engineassets/brickwall.jpg");
   
    real32 triangleVertices[] =
    {    
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f   
    };

    real32 vertices[] =
    {
          0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 
          0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 
         -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 
         -0.5f,  0.5f, 0.0f,   0.0f, 1.0f
    };

    unsigned int indices[] = 
    {
       0, 1, 3, 
       1, 2, 3  
    };   

    uint32 vao, ebo;
    uint32 vbo;

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    
    VertexBuffer *v_buffer = VertexBuffer::create(vertices, 20);
    IndexBuffer *i_buffer = IndexBuffer::create(indices, 6);
   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    triangleShader->bind();
    triangleShader->setInt("textureDiffuse", 0);
     
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        texture->bind();
        triangleShader->bind();
        
        glBindVertexArray(vao);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glfwTerminate();

    return (0);
}