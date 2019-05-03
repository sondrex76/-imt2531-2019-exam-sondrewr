#pragma once

#include <glm/mat4x4.hpp>
#include <GL/glew.h>

#include "../LightCallback.h"

namespace Renderer {
    class Camera;
    class GBuffer;
    class CameraData;
    class ColorTexture;
}

namespace Scenegraph {

    class Node {
    public:
        explicit Node(glm::mat4x4 transform);

        glm::mat4x4 transform() const { return m_transform; }

        glm::mat4x4 absoluteTransform(const glm::mat4x4 &parentAbsTransform) const;

        /**
         * Binds the active camera (if there is one) to the provided buffer.
         * @returns true if a camera was bound.
         */
        virtual bool bindActiveCamera(const glm::mat4x4 &parentAbsTransform, Renderer::CameraData &buffer) const = 0;

        /**
         * Renders all geometry in the node to the current bound target.
         */
        virtual void renderGeometry(const glm::mat4x4 &parentAbsTransform) const = 0;

        /**
         * Renders all lights to the output using the provided GBuffer.
         */
        virtual void renderLights(const glm::mat4x4 &parentAbsTransform, const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target, Renderer::RenderLightGeometryCb &geometryCb) const = 0;

    private:
        glm::mat4x4 m_transform;
    };

}
