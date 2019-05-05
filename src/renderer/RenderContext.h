#pragma once

#include "GBuffer.h"
#include "ColorTexture.h"
#include "ShaderProgram.h"
#include "CameraData.h"
#include "VertexAttribArray.h"
#include "Buffer.h"
#include "defines.h"

namespace Scenegraph {
    class Node;
}

namespace Renderer {

    class RenderContext {
    public:
        RenderContext();

        const GBuffer &gbuffer() const { return m_gbuffer; }
        GBuffer &gbuffer() { return m_gbuffer; }

        const ShaderProgram &geomProgram() const { return m_geomProgram; }
        ShaderProgram &geomProgram() { return m_geomProgram; }

        const ShaderProgram &directionalLightProgram() const { return m_directionalLightProgram; }
        ShaderProgram &directionalLightProgram() { return m_directionalLightProgram; }

        const ShaderProgram &spotLightProgram() const { return m_spotLightProgram; }
        ShaderProgram &spotLightProgram() { return m_spotLightProgram; }

        const ShaderProgram &ambientLightProgram() const { return m_ambientLightProgram; }
        ShaderProgram &ambientLightProgram() { return m_ambientLightProgram; }

        const CameraData &cameraData() const { return m_cameraData; }
        CameraData &cameraData() { return m_cameraData; }

        void render(int screenWidth, int screenHeight, const Scenegraph::Node &node);

        void startRender(int screenWidth, int screenHeight);

        void bindCamera(const Scenegraph::Node &node);

        void renderNodeGeometry(const Scenegraph::Node &node);

        void renderLights(const Scenegraph::Node &node);

        void renderPostEffects();

        void renderToScreen();

        void renderDebugFrustum(glm::mat4 frustumMatrix);

    private:
        GBuffer m_gbuffer;
        ColorTexture m_bloomPingTarget;
        ColorTexture m_bloomPongTarget;

        ShaderProgram m_geomProgram;
        ShaderProgram m_directionalLightProgram;
        ShaderProgram m_spotLightProgram;
        ShaderProgram m_ambientLightProgram;

#ifdef RENDER_LIGHT_DEBUG
        Buffer<glm::vec3> m_debugFrustumLines;
        VertexAttribArray m_debugFrustumArray;
        ShaderProgram m_debugLightFrustum;
#endif

		ShaderProgram m_postSkyboxProgram;
        ShaderProgram m_postDistanceFogProgram;
        ShaderProgram m_postBloomExtractProgram;
        ShaderProgram m_postBloomBlurProgram;
        ShaderProgram m_postBloomCompositeProgram;
        ShaderProgram m_postGradingProgram;

        ShaderProgram m_renderToScreenProgram;
        CameraData m_cameraData;
        Buffer<glm::vec2> m_renderToScreenVertices;
        VertexAttribArray m_renderToScreenArray;

        void renderPostPass(ShaderProgram &program);

        void renderBloom();

        void dispatchPostPass();
    };

}
