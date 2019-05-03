#include "GBuffer.h"

using namespace Renderer;

static Framebuffer createFb(ColorTexture *diffuseShininess, ColorTexture *specular, ColorTexture *emissive, ColorTexture *normal, ColorTexture *worldPos, DepthStencilTexture *depth) {
    ColorTexture *colors[] = {diffuseShininess, specular, emissive, normal, worldPos};
    return Framebuffer::textures(4, colors, depth);
}

GBuffer::GBuffer()
    : m_fb(createFb(&m_diffuseShininess, &m_specular, &m_emissive, &m_normal, &m_worldPos, &m_depth)) {
}

void GBuffer::setSize(int width, int height) {
    m_diffuseShininess.setSize(width, height);
    m_specular.setSize(width, height);
    m_emissive.setSize(width, height);
    m_normal.setSize(width, height);
    m_worldPos.setSize(width, height);
    m_depth.setSize(width, height);
}
