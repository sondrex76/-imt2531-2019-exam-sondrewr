#pragma once

#include <GL/glew.h>

namespace Renderer {

    class DepthStencilTexture {
    public:
        DepthStencilTexture();

        DepthStencilTexture(const DepthStencilTexture &) = delete;
        DepthStencilTexture(DepthStencilTexture &&) noexcept;

        ~DepthStencilTexture();

        void setSize(int width, int height);

        int width() const { return m_width; }

        int height() const { return m_height; }

        GLuint texture() const { return m_texture; }

    private:
        int m_width = 0;
        int m_height = 0;
        GLuint m_texture;
    };

}
