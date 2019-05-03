#pragma once

#include <GL/glew.h>

namespace Renderer {

    class ColorTexture;
    class DepthStencilTexture;

    class Framebuffer {
    public:
        static Framebuffer textures(int colorCount, ColorTexture **colors, const DepthStencilTexture *depth);
        static Framebuffer screen();

        Framebuffer(const Framebuffer &) = delete;
        Framebuffer(Framebuffer &&) noexcept;

        ~Framebuffer();

        GLuint framebuffer() const { return m_framebuffer; }

        void bind() const;

    private:
        GLuint m_framebuffer;

        explicit Framebuffer(GLuint resource);
    };

}
