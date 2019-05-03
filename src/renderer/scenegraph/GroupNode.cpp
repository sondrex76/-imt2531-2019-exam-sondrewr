#include "GroupNode.h"

using namespace Scenegraph;

GroupNode::GroupNode(glm::mat4x4 transform) : Node(transform) {}

void GroupNode::addNode(std::unique_ptr<Scenegraph::Node> node) {
    m_nodes.push_back(std::move(node));
}

bool GroupNode::bindActiveCamera(const glm::mat4x4 &parentAbsTransform, Renderer::CameraData &buffer) const {
    auto absTransform = absoluteTransform(parentAbsTransform);
    for (const auto &node : m_nodes) {
        if (node->bindActiveCamera(absTransform, buffer)) {
            return true;
        }
    }
    return false;
}

void GroupNode::renderGeometry(const glm::mat4x4 &parentAbsTransform) const {
    auto absTransform = absoluteTransform(parentAbsTransform);
    for (const auto &node : m_nodes) {
        node->renderGeometry(absTransform);
    }
}

void GroupNode::renderLights(const glm::mat4x4 &parentAbsTransform, const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target, Renderer::RenderLightGeometryCb &geometryCb) const {
    auto absTransform = absoluteTransform(parentAbsTransform);
    for (const auto &node : m_nodes) {
        node->renderLights(absTransform, gbuffer, target, geometryCb);
    }
}
