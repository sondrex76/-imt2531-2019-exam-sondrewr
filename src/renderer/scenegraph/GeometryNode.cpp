#include "GeometryNode.h"

#include "../Model.h"

using namespace Scenegraph;

GeometryNode::GeometryNode(const Renderer::Model &model, glm::mat4x4 transform, Renderer::ExtraMaterial extraMaterial)
    : Node(transform), m_model(&model), m_extraMaterial(extraMaterial) {}

bool GeometryNode::bindActiveCamera(const glm::mat4x4 &parentAbsTransform, Renderer::CameraData &buffer) const {
    // Geometry nodes don't have a camera
    return false;
}

void GeometryNode::renderGeometry(const glm::mat4x4 &parentAbsTransform) const {
    m_model->render(absoluteTransform(parentAbsTransform), m_extraMaterial);
}

void GeometryNode::renderLights(const glm::mat4x4 &parentAbsTransform, const Renderer::GBuffer &gbuffer,
                                Renderer::ColorTexture &target, Renderer::RenderLightGeometryCb &geometryCb) const {
    // Geometry nodes don't have light
}
