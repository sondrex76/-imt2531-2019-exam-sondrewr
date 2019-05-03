#pragma once

#include <glm/vec4.hpp>

#include "ImageTexture.h"

struct aiMaterial;

namespace Renderer {

    class ShaderProgram;

    class Material {
    public:
        Material(const aiMaterial *mat, const char *modelDirectory);

        Material(glm::vec3 diffuse, glm::vec3 specular, float shininess, glm::vec3 emissive);

        Material(ImageTexture diffuse, ImageTexture specular, ImageTexture shininess, ImageTexture emissive);

        void bind() const;

    private:
        /*ImageTexture m_albedo;
        ImageTexture m_metallic;
        ImageTexture m_roughness;
        ImageTexture m_emissive;*/

        ImageTexture m_diffuse;
        ImageTexture m_specular;
        ImageTexture m_shininess;
        ImageTexture m_emissive;
    };

}
