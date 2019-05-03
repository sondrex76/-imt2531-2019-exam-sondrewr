#include "PerspectiveCameraNode.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "../CameraData.h"
#include "../Math.h"

using namespace Scenegraph;

PerspectiveCameraNode::PerspectiveCameraNode(glm::vec3 pos, glm::vec3 forward, glm::vec3 up, float fov, float aspect,
                                             float nearZ, float farZ)
    : Node(glm::mat4x4(1.f)), m_projMatrix(Renderer::Math::perspectiveProjMatrix(fov, aspect, nearZ)), m_position(pos), m_forward(forward), m_up(up) {}

bool PerspectiveCameraNode::bindActiveCamera(const glm::mat4x4 &parentAbsTransform,
                                             Renderer::CameraData &buffer) const {
    glm::vec4 transformedPosHomogeneous = parentAbsTransform * glm::vec4(m_position, 1.f);
    glm::vec3 transformedPos = transformedPosHomogeneous / transformedPosHomogeneous.w;

    glm::mat4x4 dirTransform = glm::transpose(glm::inverse(parentAbsTransform));
    glm::vec3 transformedForward = dirTransform * glm::vec4(m_forward, 0.f);
    glm::vec3 transformedUp = dirTransform * glm::vec4(m_up, 0.f);

    auto viewMatrix = Renderer::Math::viewMatrix(transformedPos, transformedForward, transformedUp);
    buffer.setState(Renderer::CameraBuffer(m_projMatrix * viewMatrix, transformedPos, transformedForward));

    return true;
}

void PerspectiveCameraNode::renderGeometry(const glm::mat4x4 &parentAbsTransform) const {

}

void PerspectiveCameraNode::renderLights(const glm::mat4x4 &parentAbsTransform, const Renderer::GBuffer &gbuffer,
                                         Renderer::ColorTexture &target, Renderer::RenderLightGeometryCb &geometryCb) const {

}
