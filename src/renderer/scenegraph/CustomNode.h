#pragma once

#include "Node.h"

namespace Scenegraph {

    template<class T>
    class CustomNode final : public Node {
    public:
        CustomNode(const T &renderer, glm::mat4x4 transform)
            : Node(transform), m_renderer(&renderer) {}

        bool bindActiveCamera(const glm::mat4x4 &parentAbsTransform, Renderer::CameraData &buffer) const override {
            return false;
        }

        void renderGeometry(const glm::mat4x4 &parentAbsTransform) const override {
            m_renderer->render(absoluteTransform(parentAbsTransform));
        }

        void renderLights(const glm::mat4x4 &parentAbsTransform, const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target, Renderer::RenderLightGeometryCb &geometryCb) const override {}

    private:
        const T *m_renderer;
    };

}
