#include "ShaderProgram.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <GFX/gfx.h>

using namespace Renderer;

const char *SHADER_PATH = "resources/shaders/";

static std::string getRelativeShaderPath(const char *target) {
    std::stringstream path;
    path << SHADER_PATH;
    path << target;
    return path.str();
}

static std::string loadFile(const char *filePath) {
    std::ifstream file(filePath);
    assert(file.is_open());
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

static GLuint createShader(const char *src, GLenum shaderType) {
    GLuint shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &src, nullptr);
    glCompileShader(shaderId);

    GLint compileOk;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileOk);
    if (!compileOk) {
        int length = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
        std::string str;
        str.resize(length);
        glGetShaderInfoLog(shaderId, length, nullptr, const_cast<char *>(str.data()));
        GFX_ERROR("%s shader failed to compile with the error: %s\n", Gfx::GLEnumToString(shaderType), str.c_str());
    }
    return shaderId;
}

static GLuint createProgram(size_t programCount, GLuint *programs) {
    GLuint programId = glCreateProgram();
    for (size_t programIndex = 0; programIndex < programCount; programIndex++) {
        glAttachShader(programId, programs[programIndex]);
    }

    glLinkProgram(programId);

    GLint linkOk;
    glGetProgramiv(programId, GL_LINK_STATUS, &linkOk);
    if (!linkOk) {
        int length = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);
        std::string str;
        str.resize(length);
        glGetProgramInfoLog(programId, length, nullptr, const_cast<char *>(str.data()));
        GFX_ERROR("Program failed to link: %s\n", str.c_str());
    }

    return programId;
}

ShaderProgram ShaderProgram::vertexFragProgram(const char *vertexPath, const char *fragmentPath) {
    auto shaderCommon = loadFile(getRelativeShaderPath("common.glsl").c_str());
    auto vertexText = shaderCommon + loadFile(getRelativeShaderPath(vertexPath).c_str());
    auto fragmentText = shaderCommon + loadFile(getRelativeShaderPath(fragmentPath).c_str());

    auto vertexShader = createShader(vertexText.c_str(), GL_VERTEX_SHADER);
    auto fragmentShader = createShader(fragmentText.c_str(), GL_FRAGMENT_SHADER);
    GLuint programs[] = {vertexShader, fragmentShader};
    auto programId = createProgram(2, programs);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return ShaderProgram(programId);
}

ShaderProgram ShaderProgram::vertexGeomFragProgram(const char *vertexPath, const char *geomPath,
                                                   const char *fragmentPath) {
    auto shaderCommon = loadFile(getRelativeShaderPath("common.glsl").c_str());
    auto vertexText = shaderCommon + loadFile(getRelativeShaderPath(vertexPath).c_str());
    auto geomText = shaderCommon + loadFile(getRelativeShaderPath(geomPath).c_str());
    auto fragmentText = shaderCommon + loadFile(getRelativeShaderPath(fragmentPath).c_str());

    auto vertexShader = createShader(vertexText.c_str(), GL_VERTEX_SHADER);
    auto geomShader = createShader(geomText.c_str(), GL_GEOMETRY_SHADER);
    auto fragmentShader = createShader(fragmentText.c_str(), GL_FRAGMENT_SHADER);
    GLuint programs[] = {vertexShader, geomShader, fragmentShader};
    auto programId = createProgram(3, programs);
    glDeleteShader(vertexShader);
    glDeleteShader(geomShader);
    glDeleteShader(fragmentShader);

    return ShaderProgram(programId);
}

ShaderProgram ShaderProgram::computeProgram(const char *computePath) {
    auto shaderCommon = loadFile(getRelativeShaderPath("common.glsl").c_str());
    auto computeText = shaderCommon + loadFile(getRelativeShaderPath(computePath).c_str());
    auto computeShader = createShader(computeText.c_str(), GL_COMPUTE_SHADER);
    auto programId = createProgram(1, &computeShader);
    glDeleteShader(computeShader);

    return ShaderProgram(programId);
}

ShaderProgram::ShaderProgram(GLuint id) {
    m_id = id;
}

ShaderProgram::ShaderProgram(Renderer::ShaderProgram &&other) noexcept {
    m_id = other.m_id;
    other.m_id = 0;
}

ShaderProgram::~ShaderProgram() {
    if (m_id) {
        glDeleteProgram(m_id);
    }
}

void ShaderProgram::bind() const {
    glUseProgram(m_id);
}

void ShaderProgram::setSampler(const char *name, int unit) {
    glProgramUniform1i(m_id, glGetUniformLocation(m_id, name), unit);
}

void ShaderProgram::setUniform(const char *name, bool val) {
    glProgramUniform1i(m_id, glGetUniformLocation(m_id, name), val);
}

void ShaderProgram::setUniform(const char *name, float val) {
    glProgramUniform1f(m_id, glGetUniformLocation(m_id, name), val);
}

void ShaderProgram::setUniform(const char *name, glm::vec2 val) {
    glProgramUniform2fv(m_id, glGetUniformLocation(m_id, name), 1, &val.x);
}

void ShaderProgram::setUniform(const char *name, glm::ivec2 val) {
    glProgramUniform2iv(m_id, glGetUniformLocation(m_id, name), 1, &val.x);
}

void ShaderProgram::setUniform(const char *name, glm::vec3 val) {
    glProgramUniform3fv(m_id, glGetUniformLocation(m_id, name), 1, &val.x);
}

void ShaderProgram::setUniform(const char *name, glm::vec4 val) {
    glProgramUniform4fv(m_id, glGetUniformLocation(m_id, name), 1, &val.x);
}

void ShaderProgram::setUniform(const char *name, glm::mat4x4 val, bool transpose) {
    glProgramUniformMatrix4fv(m_id, glGetUniformLocation(m_id, name), 1, transpose, &val[0].x);
}
