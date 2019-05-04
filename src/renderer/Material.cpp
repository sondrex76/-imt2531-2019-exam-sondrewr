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
    : m_diffuse(loadMaterialTexture(mat, aiTextureType_DIFFUSE, modelDirectory, AI_MATKEY_COLOR_DIFFUSE)),
      m_specular(loadMaterialTexture(mat, aiTextureType_SPECULAR, modelDirectory, AI_MATKEY_COLOR_SPECULAR)),
      m_shininess(loadMaterialTexture(mat, aiTextureType_SHININESS, modelDirectory, AI_MATKEY_SHININESS)),
      m_emissive(loadMaterialTexture(mat, aiTextureType_EMISSIVE, modelDirectory, AI_MATKEY_COLOR_EMISSIVE)) {}

Material::Material(glm::vec3 diffuse, glm::vec3 specular, float shininess, glm::vec3 emissive)
    : m_diffuse(ImageTexture::fromColor(diffuse)),
      m_specular(ImageTexture::fromColor(specular)),
      m_shininess(ImageTexture::fromColor(glm::vec3(shininess, shininess, shininess))),
      m_emissive(ImageTexture::fromColor(emissive)) {}

Material::Material(Renderer::ImageTexture diffuse, Renderer::ImageTexture specular, Renderer::ImageTexture shininess, Renderer::ImageTexture emissive)
    : m_diffuse(std::move(diffuse)),
      m_specular(std::move(specular)),
      m_shininess(std::move(shininess)),
      m_emissive(std::move(emissive)) {}

// DEBUG
Material::Material(Renderer::ImageTexture diffuse, glm::vec3 specular, float shininess, glm::vec3 emissive)
	: m_diffuse(std::move(diffuse)),
	m_specular(ImageTexture::fromColor(specular)),
	m_shininess(ImageTexture::fromColor(glm::vec3(shininess, shininess, shininess))),
	m_emissive(ImageTexture::fromColor(emissive)) {}

void Material::bind() const {
    // Bind each texture to a unit
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_diffuse.texture());

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_specular.texture());

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_shininess.texture());

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, m_emissive.texture());
}
