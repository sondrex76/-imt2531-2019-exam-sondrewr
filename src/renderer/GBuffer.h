#pragma once

#include "ColorTexture.h"
#include "DepthStencilTexture.h"
#include "Framebuffer.h"

namespace Renderer {

    class GBuffer {
    public:
        GBuffer();

        void setSize(int width, int height);

        int width() const { return m_diffuseShininess.width(); }

        int height() const { return m_diffuseShininess.height(); }

        const ColorTexture &diffuseShininess() const { return m_diffuseShininess; }
        ColorTexture &diffuseShininess() { return m_diffuseShininess; }

        const ColorTexture &specular() const { return m_specular; }
        ColorTexture &specular() { return m_specular; }

        const ColorTexture &emissive() const { return m_emissive; }
        ColorTexture &emissive() { return m_emissive; }

        const ColorTexture &normal() const { return m_normal; }
        ColorTexture &normal() { return m_normal; }

        const ColorTexture &worldPos() const { return m_worldPos; }
        ColorTexture &worldPos() { return m_worldPos; }

        const DepthStencilTexture &depth() const { return m_depth; }
        DepthStencilTexture &depth() { return m_depth; }

        const Framebuffer &fb() const { return m_fb; }
        Framebuffer &fb() { return m_fb; }

    private:
        ColorTexture m_diffuseShininess;
        ColorTexture m_specular;
        ColorTexture m_emissive;
        ColorTexture m_normal;
        ColorTexture m_worldPos;
        DepthStencilTexture m_depth;
        Framebuffer m_fb;
    };

}
