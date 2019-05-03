#include "ColorTexture.h"

#include <GFX/gfx.h>

using namespace Renderer;

ColorTexture::ColorTexture() {
    GLuint texture;
    GFX_GL_CALL(glGenTextures(1, &texture));
    GFX_GL_CALL(glBindTexture(GL_TEXTURE_2D, texture));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    m_texture = texture;
}

ColorTexture::ColorTexture(Renderer::ColorTexture &&other) noexcept {
    m_width = other.m_width;
    m_height = other.m_height;
    m_texture = other.m_texture;

    other.m_texture = 0;
}

ColorTexture::~ColorTexture() {
    if (m_texture) {
        glDeleteTextures(1, &m_texture);
    }
}

void ColorTexture::setSize(int width, int height) {
    if (m_width == width && m_height == height) return;

    GFX_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture));
    GFX_GL_CALL(glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA32F,
        width,
        height,
        0,
        GL_RGBA,
        GL_FLOAT,
        nullptr
    ));

    m_width = width;
    m_height = height;
}
