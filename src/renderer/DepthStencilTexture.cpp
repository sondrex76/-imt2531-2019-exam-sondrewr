#include "DepthStencilTexture.h"

#include <GFX/gfx.h>

using namespace Renderer;

DepthStencilTexture::DepthStencilTexture() {
    GLuint texture;
    GFX_GL_CALL(glGenTextures(1, &texture));
    GFX_GL_CALL(glBindTexture(GL_TEXTURE_2D, texture));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    m_texture = texture;
}

DepthStencilTexture::DepthStencilTexture(Renderer::DepthStencilTexture &&other) noexcept {
    m_width = other.m_width;
    m_height = other.m_height;
    m_texture = other.m_texture;

    other.m_texture = 0;
}

DepthStencilTexture::~DepthStencilTexture() {
    if (m_texture) {
        glDeleteTextures(1, &m_texture);
    }
}

void DepthStencilTexture::setSize(int width, int height) {
    if (m_width == width && m_height == height) return;

    GFX_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture));
    //GFX_GL_CALL(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, width, height));
    GFX_GL_CALL(glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_DEPTH_COMPONENT32F,
        width,
        height,
        0,
        GL_DEPTH_COMPONENT,
        GL_FLOAT,
        nullptr
    ));

    m_width = width;
    m_height = height;
}
