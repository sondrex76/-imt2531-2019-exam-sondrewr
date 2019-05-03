#pragma once

#include <GL/glew.h>

namespace Renderer {

    class VertexAttribArray {
    public:
        VertexAttribArray();

        VertexAttribArray(const VertexAttribArray &) = delete;
        VertexAttribArray(VertexAttribArray &&) noexcept;

        ~VertexAttribArray();

        void bind() const;
        void addAttrib(GLint size, GLuint stride, GLuint offset);
        void unbind() const;

    private:
        GLuint m_vao;
        GLuint m_attribCount;
    };

}
