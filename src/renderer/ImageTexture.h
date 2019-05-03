#pragma once

#include <glm/vec3.hpp>
#include <GL/glew.h>

namespace Renderer {

    class ImageTexture {
    public:
        ImageTexture(const ImageTexture &) = delete;
        ImageTexture(ImageTexture &&) noexcept;

        ~ImageTexture();

        static ImageTexture fromFile(const char *fileName);
        static ImageTexture fromColor(glm::vec3 color);

        GLuint texture() const { return m_texture; }

        GLsizei width() const { return m_width; }

        GLsizei height() const { return m_height; }

    private:
        GLuint m_texture;
        GLsizei m_width;
        GLsizei m_height;

        ImageTexture(GLuint texture, GLsizei width, GLsizei height);
    };

}
