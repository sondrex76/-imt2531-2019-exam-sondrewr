#pragma once

#include <memory>
#include <vector>
#include <glm/mat4x4.hpp>

#include "Node.h"

namespace Scenegraph {

    class GroupNode final : public Node {
    public:
        explicit GroupNode(glm::mat4x4 transform);

        void addNode(std::unique_ptr<Node> node);

        bool bindActiveCamera(const glm::mat4x4 &parentAbsTransform, Renderer::CameraData &buffer) const override;

        void renderGeometry(const glm::mat4x4 &parentAbsTransform) const override;

        void renderLights(const glm::mat4x4 &parentAbsTransform, const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target, Renderer::RenderLightGeometryCb &geometryCb) const override;

    private:
        std::vector<std::unique_ptr<Node>> m_nodes;
    };

}
