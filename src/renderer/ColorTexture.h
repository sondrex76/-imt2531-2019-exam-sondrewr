#pragma once

#include <GL/glew.h>

namespace Renderer {

    class ColorTexture {
    public:
        ColorTexture();

        ColorTexture(const ColorTexture &) = delete;
        ColorTexture(ColorTexture &&) noexcept;

        ~ColorTexture();

        void setSize(int width, int height);

        GLuint texture() const { return m_texture; }

        int width() const { return m_width; }

        int height() const { return m_height; }

    private:
        int m_width = 0;
        int m_height = 0;
        GLuint m_texture;
    };

}
