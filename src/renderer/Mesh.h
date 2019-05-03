#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <GL/glew.h>

#include "VertexAttribArray.h"
#include "Buffer.h"

struct aiMesh;

namespace Renderer {

    class Material;
    class GBuffer;

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    class Mesh {
    public:
        Mesh(const aiMesh *, const std::vector<Material> &materials);

        Mesh(const Vertex *vertices, size_t numVertices, const uint32_t *indices, size_t numIndices, const Material &material);

        void render() const;

        const Material &material() const { return *m_material; }

        const Buffer<Vertex> &vertices() const { return m_vertices; }

        Buffer<Vertex> &vertices() { return m_vertices; }

        const Buffer<uint32_t> &indices() const { return m_indices; }

        Buffer<uint32_t> &indices() { return m_indices; }

    private:
        const Material *m_material;
        VertexAttribArray m_vao;
        Buffer<Vertex> m_vertices;
        Buffer<uint32_t> m_indices;

        void setupVao();
    };
}
