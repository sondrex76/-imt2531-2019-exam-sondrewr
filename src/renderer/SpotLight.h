#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "LightCallback.h"

namespace Renderer {

    class RenderContext;
    class GBuffer;
    class ColorTexture;

    class SpotLight {
    public:
        SpotLight(
            glm::vec3 position,
            glm::vec3 direction,
            glm::vec3 color,
            float cutoffRadians,
            float focus,
            float ambient,
            float radius,
            float falloff,
            RenderContext &renderContext
        );

        const glm::vec3 &position() const { return m_position; }

        glm::vec3 &position() { return m_position; }

        const glm::vec3 &color() const { return m_color; }

        glm::vec3 &color() { return m_color; }

        const float &ambient() const { return m_ambient; }

        float &ambient() { return m_ambient; }

        const float &radius() const { return m_radius; }

        float &radius() { return m_radius; }

        const float &falloff() const { return m_falloff; }

        float &falloff() { return m_falloff; }

        void renderDebug(glm::mat4x4 transform) const {}

        void render(const GBuffer &gbuffer, ColorTexture &target, glm::mat4x4 transform, RenderLightGeometryCb &geometryCb) const;

    private:
        RenderContext *m_renderContext;
        glm::vec3 m_position;
        glm::vec3 m_direction;
        glm::vec3 m_color;
        float m_cutoffRadians;
        float m_focus;
        float m_ambient;
        float m_radius;
        float m_falloff;
    };

}
