#pragma once

#include "shader.h"

namespace XEngine
{
    namespace Rendering
    {
        class Shaders
        {
        public:
            static Shader rgba;
            static Shader lightShader;
            static Shader cubeMap;
            static Shader bPhongModelShader;
            static Shader textShader;
            static Shader lightMapShader;
            static Shader depthMapQuad;
            static Shader shadowShader;
            static Shader normalMappingShader;
            static Shader blurShader;
            static Shader bloomShader;
            static Shader mixedShader;
            static Shader dispShader;
            static Shader shaderGeometryPass;
            static Shader shaderLightingPass;
        };
    }
}
