#include "SpotLight.h"

#include "RenderContext.h"

using namespace Renderer;

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float cutoffRadians, float focus,
                     float ambient, float radius, float falloff, Renderer::RenderContext &renderContext)
    : m_renderContext(&renderContext), m_position(position), m_direction(direction), m_color(color),
      m_cutoffRadians(cutoffRadians), m_focus(focus), m_ambient(ambient), m_radius(radius), m_falloff(falloff) {}

void SpotLight::render(const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target, glm::mat4x4 transform,
                       Renderer::RenderLightGeometryCb &geometryCb) const {
    glm::vec3 transformedPosition = transform * glm::vec4(m_position.x, m_position.y, m_position.z, 1);
    glm::vec3 transformedDirection = glm::normalize(glm::vec3(glm::transpose(glm::inverse(transform)) * glm::vec4(m_direction.x, m_direction.y, m_direction.z, 0)));

    ShaderProgram &program = m_renderContext->spotLightProgram();
    program.bind();
    program.setUniform("lightPosition", transformedPosition);
    program.setUniform("lightDirection", transformedDirection);
    program.setUniform("lightColor", m_color);
    program.setUniform("lightCutoffAngle", m_cutoffRadians);
    program.setUniform("lightFocus", m_focus);
    program.setUniform("lightAmbient", m_ambient);
    program.setUniform("lightB", 1.f / (m_radius * m_radius * 0.01f));
    program.setUniform("lightFalloff", m_falloff);
    program.setUniform("lightMaxRadius", m_radius * 5);

    glBindImageTexture(0, target.texture(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
    glBindImageTexture(1, gbuffer.diffuseShininess().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
    glBindImageTexture(2, gbuffer.specular().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
    glBindImageTexture(3, gbuffer.normal().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
    glBindImageTexture(4, gbuffer.worldPos().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);

    glDispatchCompute((gbuffer.width() + 7) / 8, (gbuffer.height() + 7) / 8, 1);

    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}
