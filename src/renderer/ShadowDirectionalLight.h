#pragma once

#include "DirectionalLight.h"
#include "DepthStencilTexture.h"
#include "LightCallback.h"
#include "Framebuffer.h"

namespace Renderer {

    class ShadowDirectionalLight {
    public:
        ShadowDirectionalLight(
            DirectionalLight baseLight,
            glm::vec3 pos,
            glm::vec3 up,
            glm::vec2 horizontalRange,
            glm::vec2 verticalRange,
            glm::vec2 depthRange,
            glm::uvec2 resolution,
            RenderContext &renderContext
        );

        const DirectionalLight &baseLight() const { return m_baseLight; }

        DirectionalLight &baseLight() { return m_baseLight; }

        const glm::vec3 &pos() const { return m_pos; }

        glm::vec3 &pos() { return m_pos; }

        const glm::vec3 &up() const { return m_up; }

        glm::vec3 &up() { return m_up; }

        const glm::vec2 &horizontalRange() const { return m_horizontalRange; }

        glm::vec2 &horizontalRange() { return m_horizontalRange; }

        const glm::vec2 &verticalRange() const { return m_verticalRange; }

        glm::vec2 &verticalRange() { return m_verticalRange; }

        const glm::vec2 &depthRange() const { return m_depthRange; }

        glm::vec2 &depthRange() { return m_depthRange; }

        void renderDebug(glm::mat4x4 transform) const;

        void render(const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target, glm::mat4x4 transform, RenderLightGeometryCb &geometryCb) const;

    private:
        RenderContext *m_renderContext;
        DirectionalLight m_baseLight;
        glm::vec3 m_pos;
        glm::vec3 m_up;
        glm::vec2 m_horizontalRange;
        glm::vec2 m_verticalRange;
        glm::vec2 m_depthRange;
        DepthStencilTexture m_shadowMap;
        Framebuffer m_shadowMapFb;

        void getViewProjMatrix(glm::mat4x4 transform, glm::mat4x4 &out_viewProjMatrix, glm::vec3 &out_transformedPos, glm::vec3 &out_transformedDirection) const;
    };

}
