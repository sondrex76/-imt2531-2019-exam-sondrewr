#include "Framebuffer.h"

#include <vector>
#include <GFX/gfx.h>
#include <cassert>

#include "ColorTexture.h"
#include "DepthStencilTexture.h"

using namespace Renderer;

Framebuffer::Framebuffer(GLuint resource) : m_framebuffer(resource) {}

Framebuffer Framebuffer::textures(int colorCount, Renderer::ColorTexture **colors, const Renderer::DepthStencilTexture *depth) {
    GLuint fb;

    GFX_GL_CALL(glGenFramebuffers(1, &fb));
    GFX_GL_CALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fb));
    if (colorCount > 0) {
        std::vector<GLuint> buffers;
        buffers.reserve(colorCount);

        auto colorIndex = 0;
        for (auto i = 0; i < colorCount; i++) {
            auto color = colors[i];
            if (color == nullptr) {
                buffers.push_back(GL_NONE);
            } else {
                auto attachment = (GLenum) (GL_COLOR_ATTACHMENT0 + colorIndex);
                colorIndex++;
                buffers.push_back(attachment);
                GFX_GL_CALL(glFramebufferTexture(GL_DRAW_FRAMEBUFFER, attachment, color->texture(), 0));
            }
        }
        GFX_GL_CALL(glDrawBuffers(colorCount, &buffers[0]));
    } else {
        GFX_GL_CALL(glDrawBuffer(GL_NONE));
    }

    if (depth) {
        GFX_GL_CALL(glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth->texture(), 0));
    }

    GFX_GL_CALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));

    return Framebuffer(fb);
}

Framebuffer Framebuffer::screen() {
    return Framebuffer(0);
}

Framebuffer::Framebuffer(Renderer::Framebuffer &&other) noexcept {
    m_framebuffer = other.m_framebuffer;
    other.m_framebuffer = 0;
}

Framebuffer::~Framebuffer() {
    if (m_framebuffer) {
        glDeleteFramebuffers(1, &m_framebuffer);
    }
}

void Framebuffer::bind() const {
    GFX_GL_CALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_framebuffer));
}
