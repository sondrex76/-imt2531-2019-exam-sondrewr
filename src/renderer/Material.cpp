#include "Material.h"

#include <cassert>
#include <assimp/scene.h>
#include <string>
#include <sstream>

#include "ShaderProgram.h"

using namespace Renderer;

static std::string getMaterialFilePath(const char *modelDirectory, const char *materialName) {
    std::stringstream path;
    path << modelDirectory;
    if (modelDirectory[strlen(modelDirectory) - 1] != '/') path << "/";
    path << materialName;
    return path.str();
}

static ImageTexture loadMaterialTexture(const aiMaterial *mat, aiTextureType type, const char *modelDirectory, const char *colorProp, unsigned propType, unsigned propIdx) {
    if (mat->GetTextureCount(type) > 0) {
        // There's a texture for this property
        aiString pathStr;
        mat->GetTexture(type, 0, &pathStr);
        auto texPath = getMaterialFilePath(modelDirectory, pathStr.C_Str());
        return ImageTexture::fromFile(texPath.c_str());
    } else {
        // Use a solid color for the property
        aiColor3D color;
        auto success = mat->Get(colorProp, propType, propIdx, color);
        if (success == aiReturn_SUCCESS) {
            return ImageTexture::fromColor(glm::vec3(color.r, color.g, color.b));
        } else {
            // If the property doesn't exist, just use black
            return ImageTexture::fromColor(glm::vec3(0, 0, 0));
        }
    }
}

Material::Material(const aiMaterial *mat, const char *modelDirectory)
// Assimp texture types don't map too well to PBR parameters, so we just do
// a best guess here.
    : m_albedo(loadMaterialTexture(mat, aiTextureType_DIFFUSE, modelDirectory, AI_MATKEY_COLOR_DIFFUSE)),
      m_metallic(loadMaterialTexture(mat, aiTextureType_SHININESS, modelDirectory, AI_MATKEY_COLOR_REFLECTIVE)),
      m_roughness(loadMaterialTexture(mat, aiTextureType_SPECULAR, modelDirectory, AI_MATKEY_COLOR_SPECULAR)),
      m_emissive(loadMaterialTexture(mat, aiTextureType_EMISSIVE, modelDirectory, AI_MATKEY_COLOR_EMISSIVE)) {}

Material::Material(glm::vec3 albedo, float metallic, float roughness, glm::vec3 emissive)
    : m_albedo(ImageTexture::fromColor(albedo)),
      m_metallic(ImageTexture::fromColor(glm::vec3(metallic))),
      m_roughness(ImageTexture::fromColor(glm::vec3(roughness))),
      m_emissive(ImageTexture::fromColor(emissive)) {}

Material::Material(Renderer::ImageTexture albedo, Renderer::ImageTexture metallic, Renderer::ImageTexture roughness,
                   Renderer::ImageTexture emissive)
    : m_albedo(std::move(albedo)),
      m_metallic(std::move(metallic)),
      m_roughness(std::move(roughness)),
      m_emissive(std::move(emissive)) {}

void Material::bind() const {
    // Bind each texture to a unit
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_albedo.texture());

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_metallic.texture());

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_roughness.texture());

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, m_emissive.texture());
}
