#pragma once

#include <glm/mat4x4.hpp>

namespace Renderer::Math {

    glm::mat4x4 perspectiveProjMatrix(float fovY, float aspect, float zNear);

    glm::mat4x4 viewMatrix(glm::vec3 pos, glm::vec3 forward, glm::vec3 up);

}
