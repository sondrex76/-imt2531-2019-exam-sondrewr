#pragma once

#include "Node.h"

namespace Scenegraph {

    class PerspectiveCameraNode final : public Node {
    public:
        PerspectiveCameraNode(glm::vec3 pos, glm::vec3 forward, glm::vec3 up, float fov, float aspect, float nearZ, float farZ);

        bool bindActiveCamera(const glm::mat4x4 &parentAbsTransform, Renderer::CameraData &buffer) const override;

        void renderGeometry(const glm::mat4x4 &parentAbsTransform) const override;

        void renderLights(const glm::mat4x4 &parentAbsTransform, const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target, Renderer::RenderLightGeometryCb &geometryCb) const override;

    private:
        glm::mat4x4 m_projMatrix;
        glm::vec3 m_position;
        glm::vec3 m_forward;
        glm::vec3 m_up;
    };

}
