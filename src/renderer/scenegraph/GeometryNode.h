#pragma once

#include "Node.h"
#include "../ExtraMaterial.h"

namespace Renderer {
    class Model;
}

namespace Scenegraph {

    class GeometryNode final : public Node {
    public:
        GeometryNode(const Renderer::Model &model, glm::mat4x4 transform, Renderer::ExtraMaterial extraMaterial = Renderer::ExtraMaterial());

        bool bindActiveCamera(const glm::mat4x4 &parentAbsTransform, Renderer::CameraData &buffer) const override;

        void renderGeometry(const glm::mat4x4 &parentAbsTransform) const override;

        void renderLights(const glm::mat4x4 &parentAbsTransform, const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target, Renderer::RenderLightGeometryCb &geometryCb) const override;

    private:
        const Renderer::Model *m_model;
        Renderer::ExtraMaterial m_extraMaterial;
    };

}
