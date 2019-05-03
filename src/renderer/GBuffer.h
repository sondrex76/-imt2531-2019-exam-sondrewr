#pragma once

#include "ColorTexture.h"
#include "DepthStencilTexture.h"
#include "Framebuffer.h"

namespace Renderer {

    class GBuffer {
    public:
        GBuffer();

        void setSize(int width, int height);

        int width() const { return m_albedoMetallic.width(); }

        int height() const { return m_albedoMetallic.height(); }

        const ColorTexture &albedoMetallic() const { return m_albedoMetallic; }
        ColorTexture &albedoMetallic() { return m_albedoMetallic; }

        const ColorTexture &normalRoughness() const { return m_normalRoughness; }
        ColorTexture &normalRoughness() { return m_normalRoughness; }

        const ColorTexture &emissive() const { return m_emissive; }
        ColorTexture &emissive() { return m_emissive; }

        const ColorTexture &worldPos() const { return m_worldPos; }
        ColorTexture &worldPos() { return m_worldPos; }

        const DepthStencilTexture &depth() const { return m_depth; }
        DepthStencilTexture &depth() { return m_depth; }

        const Framebuffer &fb() const { return m_fb; }
        Framebuffer &fb() { return m_fb; }

    private:
        ColorTexture m_albedoMetallic;
        ColorTexture m_normalRoughness;
        ColorTexture m_emissive;
        ColorTexture m_worldPos;
        DepthStencilTexture m_depth;
        Framebuffer m_fb;
    };

}
