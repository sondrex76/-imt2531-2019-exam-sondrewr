#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "LightCallback.h"

namespace Renderer {

    class RenderContext;
    class GBuffer;
    class ColorTexture;

    class AmbientLight {
    public:
        AmbientLight(glm::vec3 color, RenderContext &renderContext);

        const glm::vec3 &color() const { return m_color; }

        glm::vec3 &color() { return m_color; }

        void renderDebug(glm::mat4x4 transform) const {}

        void render(const GBuffer &gbuffer, ColorTexture &target, glm::mat4x4 transform, RenderLightGeometryCb &geometryCb) const;

    private:
        RenderContext *m_renderContext;
        glm::vec3 m_color;
    };

}
