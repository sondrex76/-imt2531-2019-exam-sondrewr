#pragma once

#include <GL/glew.h>
#include <GFX/gfx.h>

namespace Renderer {

    template<class T>
    class Buffer;

    template<class T>
    class MappedBuffer {
        friend class Buffer<T>;

    public:
        MappedBuffer(const MappedBuffer &) = delete;
        MappedBuffer(MappedBuffer &&other) noexcept {
            m_length = other.m_length;
            m_items = other.m_items;
            m_target = other.m_target;

            other.m_items = nullptr;
        }

        ~MappedBuffer() {
            if (m_items) {
                glUnmapBuffer(m_target);
            }
        }

        GLsizei length() { return m_length; }
        T *items() { return m_items; }

    private:
        MappedBuffer(GLsizei length, GLenum target, GLuint buffer) {
            GFX_GL_CALL(glBindBuffer(target, buffer));
            m_length = length;
            m_items = static_cast<T*>(glMapBuffer(target, GL_WRITE_ONLY));
            m_target = target;
        }

        GLsizei m_length;
        T *m_items;
        GLenum m_target;
    };

    template<class T>
    class Buffer {
    public:
        Buffer(GLsizei length, GLenum target, GLenum usage)
            : m_length(length), m_target(target), m_usage(usage) {
            GFX_GL_CALL(glGenBuffers(1, &m_buffer));
            GFX_GL_CALL(glBindBuffer(target, m_buffer));

            // Ensure that the size we pass to glBufferData is a multiple of 16
            GLsizei dataSize = length * sizeof(T);
            GLsizei alignedSize = (dataSize + 15) / 16 * 16;
            GFX_GL_CALL(glBufferData(target, alignedSize, nullptr, usage));
        }

        Buffer(const Buffer &) = delete;
        Buffer(Buffer &&other) noexcept {
            m_length = other.m_length;
            m_target = other.m_target;
            m_usage = other.m_usage;
            m_buffer = other.m_buffer;

            other.m_buffer = 0;
        }

        ~Buffer() {
			if (m_buffer != 0) {
				glDeleteBuffers(1, &m_buffer);
			}
        }

        GLsizei length() const { return m_length; }

        GLuint buffer() const { return m_buffer; }

        void bind() const {
            GFX_GL_CALL(glBindBuffer(m_target, m_buffer));
        }

        MappedBuffer<T> map() {
            return MappedBuffer<T>(m_length, m_target, m_buffer);
        }

        void upload(GLsizei length, const T *items) {
            bind();
            GFX_GL_CALL(glBufferData(m_target, length * sizeof(T), items, m_usage));
        }

    private:
        GLsizei m_length;
        GLenum m_target;
        GLenum m_usage;
        GLuint m_buffer;
    };

}
