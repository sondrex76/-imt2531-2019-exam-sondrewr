#include "Model.h"

#include <string>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GFX/gfx.h>

#include "Material.h"
#include "Mesh.h"
#include "RenderContext.h"

using namespace Renderer;

const char *OBJ_PATH = "resources/obj/";

static std::string getRelativeObjPath(const char *target) {
    std::stringstream path;
    path << OBJ_PATH;
    path << target;
    return path.str();
}

static void loadSceneMaterials(const aiScene *scene, std::vector<Material> &materials, const char *modelDirectory) {
    materials.reserve(scene->mNumMaterials);
    for (unsigned i = 0; i < scene->mNumMaterials; i++) {
        materials.emplace_back(scene->mMaterials[i], modelDirectory);
    }
}

static void loadSceneMeshes(const aiScene *scene, const std::vector<Material> &materials, std::vector<Mesh> &meshes) {
    meshes.reserve(scene->mNumMeshes);
    for (unsigned i = 0; i < scene->mNumMeshes; i++) {
        // Ignore the mesh if faces have < 3 indices
        auto mesh = scene->mMeshes[i];
        if (mesh->mNumFaces > 0 && mesh->mFaces[0].mNumIndices >= 3) {
            meshes.emplace_back(mesh, materials);
        }
    }
}

Model Model::fromObjFile(const char *fileName, RenderContext &renderContext) {
    auto relativePath = getRelativeObjPath(fileName);

    Assimp::Importer importer;

    unsigned flags = aiProcess_JoinIdenticalVertices
                     | aiProcess_Triangulate
                     | aiProcess_GenNormals
                     | aiProcess_PreTransformVertices
                     | aiProcess_RemoveRedundantMaterials
                     | aiProcess_OptimizeMeshes
                     | aiProcess_FlipUVs;
    assert(importer.ValidateFlags(flags));

    auto scene = importer.ReadFile(
        relativePath.c_str(),
        flags
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        GFX_ERROR("ASSIMP: %s", importer.GetErrorString());
    }

    std::string directory;
    auto last_slash_index = relativePath.rfind('/');
    if (last_slash_index != std::string::npos) {
        directory = relativePath.substr(0, last_slash_index + 1);
    }

    std::vector<Material> materials;
    std::vector<Mesh> meshes;
    loadSceneMaterials(scene, materials, directory.c_str());
    loadSceneMeshes(scene, materials, meshes);

    return Model(renderContext, std::move(materials), std::move(meshes));
}

Model Model::fromGeometry(const Renderer::Vertex *vertices, size_t numVertices, const uint32_t *indices,
                          size_t numIndices, Renderer::Material material, RenderContext &renderContext) {
    std::vector<Material> materials;
    materials.push_back(std::move(material));

    std::vector<Mesh> meshes;
    meshes.emplace_back(vertices, numVertices, indices, numIndices, materials[0]);

    return Model(renderContext, std::move(materials), std::move(meshes));
}

Model::Model(Renderer::RenderContext &renderContext, std::vector<Renderer::Material> materials,
             std::vector<Renderer::Mesh> meshes)
    : m_renderContext(&renderContext), m_materials(std::move(materials)), m_meshes(std::move(meshes)) {}

void Model::render(glm::mat4x4 transform, ExtraMaterial extraMaterial) const {
    m_renderContext->geomProgram().setUniform("modelMatrix", transform);
    m_renderContext->geomProgram().setUniform("modelNormMatrix", glm::transpose(glm::inverse(transform)));
    m_renderContext->geomProgram().setUniform("extraEmissive", extraMaterial.emissive);

    for (const auto &mesh : m_meshes) {
        mesh.render();
    }
}
