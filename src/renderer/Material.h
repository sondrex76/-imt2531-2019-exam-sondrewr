#pragma once

#include <glm/vec4.hpp>

#include "ImageTexture.h"

struct aiMaterial;

namespace Renderer {

    class ShaderProgram;

    class Material {
    public:
        Material(const aiMaterial *mat, const char *modelDirectory);

        Material(glm::vec3 albedo, float metallic, float roughness, glm::vec3 emissive);

        Material(ImageTexture albedo, ImageTexture metallic, ImageTexture roughness, ImageTexture emissive);

        void bind() const;

    private:
        ImageTexture m_albedo;
        ImageTexture m_metallic;
        ImageTexture m_roughness;
        ImageTexture m_emissive;
    };

}
