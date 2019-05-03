#include "ImageTexture.h"

#include <stb/stb_image.h>
#include <cassert>
#include <GFX/gfx.h>

using namespace Renderer;

ImageTexture::ImageTexture(Renderer::ImageTexture &&other) noexcept {
    m_texture = other.m_texture;
    m_width = other.m_width;
    m_height = other.m_height;

    other.m_texture = 0;
}

ImageTexture::~ImageTexture() {
    if (m_texture) {
        glDeleteTextures(1, &m_texture);
    }
}

ImageTexture ImageTexture::fromFile(const char *fileName) {
    int textureWidth = 0, textureHeight = 0;
    auto imageData = stbi_load(fileName, &textureWidth, &textureHeight, nullptr, 4);
    assert(imageData && textureWidth && textureHeight);

    GLuint texture;
    GFX_GL_CALL(glGenTextures(1, &texture));
    GFX_GL_CALL(glBindTexture(GL_TEXTURE_2D, texture));
    GFX_GL_CALL(glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        textureWidth,
        textureHeight,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        imageData
    ));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    stbi_image_free(imageData);

    return ImageTexture(texture, textureWidth, textureHeight);
}

ImageTexture ImageTexture::fromColor(glm::vec3 color) {
    GLuint texture;
    GFX_GL_CALL(glGenTextures(1, &texture));
    GFX_GL_CALL(glBindTexture(GL_TEXTURE_2D, texture));
    GFX_GL_CALL(glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        1,
        1,
        0,
        GL_RGBA,
        GL_FLOAT,
        &color
    ));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GFX_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    return ImageTexture(texture, 1, 1);
}

ImageTexture::ImageTexture(GLuint texture, GLsizei width, GLsizei height)
    : m_texture(texture), m_width(width), m_height(height) {}
