#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "LightCallback.h"

namespace Renderer {

    class RenderContext;
    class GBuffer;
    class ColorTexture;
    class DepthStencilTexture;

    class DirectionalLight {
    public:
        DirectionalLight(glm::vec3 direction, glm::vec3 color, float ambient, RenderContext &renderContext);

        const glm::vec3 &direction() const { return m_direction; }

        glm::vec3 &direction() { return m_direction; }

        const glm::vec3 &color() const { return m_color; }

        glm::vec3 &color() { return m_color; }

        const float &ambient() const { return m_ambient; }

        float &ambient() { return m_ambient; }

        void renderDebug(glm::mat4x4 transform) const {}

        void render(const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target, glm::mat4x4 transform, Renderer::RenderLightGeometryCb &geometryCb) const;

        void renderWithShadowMap(const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target,
                                 const Renderer::DepthStencilTexture *shadowMap, glm::mat4x4 shadowMapViewProj,
                                 glm::mat4x4 transform) const;

    private:
        RenderContext *m_renderContext;
        glm::vec3 m_direction;
        glm::vec3 m_color;
        float m_ambient;
    };

}
