#include "Math.h"

using namespace Renderer;

glm::mat4x4 Math::perspectiveProjMatrix(float fovY, float aspect, float zNear) {
    float f = 1.f / ::tanf(fovY / 2.f);
    return glm::mat4(
        f / aspect, 0.f, 0.f,   0.f,
        0.f,        f,   0.f,   0.f,
        0.f,        0.f, 0.f,  -1.f,
        0.f,        0.f, zNear, 0.f
    );
}

glm::mat4x4 Math::viewMatrix(glm::vec3 pos, glm::vec3 forward, glm::vec3 up) {
    auto right = glm::cross(forward, up);
    glm::mat4x4 r = {
        glm::vec4(right, 0.f),
        glm::vec4(up, 0.f),
        glm::vec4(forward, 0.f),
        glm::vec4(pos, 1.f)
    };
    return glm::inverse(r);
}
