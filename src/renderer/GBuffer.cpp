#include "GBuffer.h"

using namespace Renderer;

static Framebuffer createFb(ColorTexture *albedoMetallic, ColorTexture *normalRoughness, ColorTexture *emissive, ColorTexture *worldPos, DepthStencilTexture *depth) {
    ColorTexture *colors[] = {albedoMetallic, normalRoughness, emissive, worldPos};
    return Framebuffer::textures(4, colors, depth);
}

GBuffer::GBuffer()
    : m_fb(createFb(&m_albedoMetallic, &m_normalRoughness, &m_emissive, &m_worldPos, &m_depth)) {
}

void GBuffer::setSize(int width, int height) {
    m_albedoMetallic.setSize(width, height);
    m_normalRoughness.setSize(width, height);
    m_emissive.setSize(width, height);
    m_worldPos.setSize(width, height);
    m_depth.setSize(width, height);
}
