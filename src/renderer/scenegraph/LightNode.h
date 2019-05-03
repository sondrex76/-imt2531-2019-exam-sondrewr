#pragma once

#include "Node.h"
#include "../defines.h"

namespace Scenegraph {

    template<class TLight>
    class LightNode final : public Node {
    public:
        LightNode(const TLight &light, glm::mat4x4 transform) : Node(transform), m_light(&light) {}

        bool bindActiveCamera(const glm::mat4x4 &parentAbsTransform, Renderer::CameraData &buffer) const override {
            // Lights don't have a camera
            return false;
        }

        void renderGeometry(const glm::mat4x4 &parentAbsTransform) const override {
#ifdef RENDER_LIGHT_DEBUG
            m_light->renderDebug(absoluteTransform(parentAbsTransform));
#endif
        }

        void renderLights(const glm::mat4x4 &parentAbsTransform, const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target, Renderer::RenderLightGeometryCb &geometryCb) const override {
            m_light->render(gbuffer, target, absoluteTransform(parentAbsTransform), geometryCb);
        }

    private:
        const TLight *m_light;
    };

}
