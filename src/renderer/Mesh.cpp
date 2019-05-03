#include "Mesh.h"

#include <sstream>
#include <fstream>
#include <GFX/gfx.h>
#include <assimp/scene.h>

#include "Material.h"

using namespace Renderer;

static void uploadVertices(const aiMesh *mesh, Buffer<Vertex> &vertices) {
    auto vertexMap = vertices.map();
    for (unsigned i = 0; i < mesh->mNumVertices; i++) {
        const auto &sourcePos = mesh->mVertices[i];
        const auto &sourceNormal = mesh->mNormals[i];

        Vertex vertex;
        vertex.position = glm::vec3(sourcePos.x, sourcePos.y, sourcePos.z);
        vertex.normal = glm::vec3(sourceNormal.x, sourceNormal.y, sourceNormal.z);
        if (mesh->mTextureCoords[0]) {
            const auto &sourceUv = mesh->mTextureCoords[0][i];
            vertex.uv = glm::vec2(sourceUv.x, sourceUv.y);
        } else {
            vertex.uv = glm::vec2(0, 0);
        }

        vertexMap.items()[i] = vertex;
    }
}

static void uploadIndices(const aiMesh *mesh, Buffer<uint32_t> &indices) {
    auto indexMap = indices.map();
    for (unsigned i = 0; i < mesh->mNumFaces; i++) {
        const auto &sourceFace = mesh->mFaces[i];
        assert(sourceFace.mNumIndices == 3);
        indexMap.items()[i * 3 + 0] = sourceFace.mIndices[0];
        indexMap.items()[i * 3 + 1] = sourceFace.mIndices[1];
        indexMap.items()[i * 3 + 2] = sourceFace.mIndices[2];
    }
}

static void copyVertices(const Vertex *vertices, size_t vertexCount, Buffer<Vertex> &vertexBuffer) {
    auto vertexMap = vertexBuffer.map();
    for (size_t i = 0; i < vertexCount; i++) {
        vertexMap.items()[i] = vertices[i];
    }
}

static void copyIndices(const uint32_t *indices, size_t indexCount, Buffer<uint32_t> &indexBuffer) {
    auto indexMap = indexBuffer.map();
    for (size_t i = 0; i < indexCount; i++) {
        indexMap.items()[i] = indices[i];
    }
}

Mesh::Mesh(const aiMesh *mesh, const std::vector<Renderer::Material> &materials)
    : m_material(&materials[mesh->mMaterialIndex]),
      m_vertices(mesh->mNumVertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW),
      m_indices(mesh->mNumFaces * 3, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW) {
    uploadVertices(mesh, m_vertices);
    uploadIndices(mesh, m_indices);

    setupVao();
}

Mesh::Mesh(const Renderer::Vertex *vertices, size_t numVertices, const uint32_t *indices, size_t numIndices,
           const Renderer::Material &material)
    : m_material(&material),
      m_vertices(numVertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW),
      m_indices(numIndices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW) {
    copyVertices(vertices, numVertices, m_vertices);
    copyIndices(indices, numIndices, m_indices);

    setupVao();
}

void Mesh::render() const {
    m_material->bind();
    m_vao.bind();
    m_vertices.bind();
    m_indices.bind();
    GFX_GL_CALL(glDrawElements(GL_TRIANGLES, m_indices.length(), GL_UNSIGNED_INT, nullptr));
    m_vao.unbind();
}

void Mesh::setupVao() {
    m_vao.bind();
    m_vertices.bind();
    m_indices.bind();
    m_vao.addAttrib(3, 8, 0); // position
    m_vao.addAttrib(3, 8, 3); // normal
    m_vao.addAttrib(2, 8, 6); // UV
    m_vao.unbind();
}
