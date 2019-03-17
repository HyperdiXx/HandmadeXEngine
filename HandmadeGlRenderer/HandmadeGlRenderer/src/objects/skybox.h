#pragma once

#ifndef SKYBOXH
#define SKYBOXH

#include "src/core/rendering/pipeline/shader.h"
#include "src/core/rendering/texture.h"
#include "src/core/cameras/camera.h"
#include "src/core/rendering/openglnew/vao.h"

class Skybox
{
public:
    Skybox() 
    {
        sky = (GeometryBuffer*)malloc(sizeof(GeometryBuffer));
    };
    ~Skybox()
    {
        free(sky);
    }

    void createSkybox();
    void initShader();
    void renderSkybox(Shader * shader, XEngine::Camera *cam, glm::mat4& v, glm::mat4& proj, uint32& tex);
    GeometryBuffer* getGeometryBuffer() { return sky; };
private:
    GeometryBuffer *sky;
};


#endif // !SKYBOX

