#pragma once

#include <glm/mat4x4.hpp>
#include <vector>

#include "Material.h"
#include "Mesh.h"
#include "ExtraMaterial.h"

struct aiScene;

namespace Renderer {

    class RenderContext;
    class GBuffer;

    class Model {
    public:
        static Model fromObjFile(const char *fileName, RenderContext &renderContext);

        static Model fromGeometry(const Vertex *vertices, size_t numVertices, const uint32_t *indices, size_t numIndices, Material material, RenderContext &renderContext);

        void render(glm::mat4x4 transform, ExtraMaterial extraMaterial = ExtraMaterial()) const;

    private:
        RenderContext *m_renderContext;
        std::vector<Material> m_materials;
        std::vector<Mesh> m_meshes;

        Model(RenderContext &renderContext, std::vector<Material> materials, std::vector<Mesh> meshes);
    };

}
