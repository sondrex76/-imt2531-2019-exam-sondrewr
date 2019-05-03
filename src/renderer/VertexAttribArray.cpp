#include "VertexAttribArray.h"

using namespace Renderer;

VertexAttribArray::VertexAttribArray() : m_attribCount(0) {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    m_vao = vao;
}

VertexAttribArray::VertexAttribArray(Renderer::VertexAttribArray &&other) noexcept {
    m_vao = other.m_vao;
    m_attribCount = other.m_attribCount;
    other.m_vao = 0;
}

VertexAttribArray::~VertexAttribArray() {
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
    }
}

void VertexAttribArray::bind() const {
    glBindVertexArray(m_vao);
}

// Adds attribute to VAO
void VertexAttribArray::addAttrib(GLint size, GLuint stride, GLuint offset) {
    auto attribIndex = m_attribCount++;
    glVertexAttribPointer(attribIndex, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(offset * sizeof(float)));
    glEnableVertexAttribArray(attribIndex);
}

void VertexAttribArray::unbind() const {
    glBindVertexArray(0);
}
