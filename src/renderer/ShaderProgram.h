#pragma once

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace Renderer {

    class ShaderProgram {
    public:
        static ShaderProgram vertexFragProgram(const char *vertexPath, const char *fragmentPath);

        static ShaderProgram vertexGeomFragProgram(const char *vertexPath, const char *geomPath, const char *fragmentPath);

        static ShaderProgram computeProgram(const char *computePath);

        ShaderProgram(const ShaderProgram &) = delete;

        ShaderProgram(ShaderProgram &&) noexcept;

        ~ShaderProgram();

        void bind() const;

        void setSampler(const char *name, int unit);

        void setUniform(const char *name, bool val);

        void setUniform(const char *name, float val);

        void setUniform(const char *name, glm::vec2 val);

        void setUniform(const char *name, glm::ivec2 val);

        void setUniform(const char *name, glm::vec3 val);

        void setUniform(const char *name, glm::vec4 val);

        void setUniform(const char *name, glm::mat4x4 val, bool transpose = false);

    private:
        GLuint m_id;

        explicit ShaderProgram(GLuint id);
    };

}
