#include "DirectionalLight.h"

#include "RenderContext.h"

using namespace Renderer;

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, float ambient, RenderContext &renderContext)
    : m_renderContext(&renderContext), m_direction(direction), m_color(color), m_ambient(ambient) {}

void DirectionalLight::render(const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target,
                              glm::mat4x4 transform, Renderer::RenderLightGeometryCb &) const {
    renderWithShadowMap(gbuffer, target, nullptr, glm::mat4x4(1.), transform);
}

void DirectionalLight::renderWithShadowMap(const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target,
                                           const Renderer::DepthStencilTexture *shadowMap,
                                           glm::mat4x4 shadowMapViewProj,
                                           glm::mat4x4 transform) const {
    glm::vec3 transformedDirection = glm::normalize(glm::vec3(glm::transpose(glm::inverse(transform)) * glm::vec4(m_direction.x, m_direction.y, m_direction.z, 0)));

    ShaderProgram &program = m_renderContext->directionalLightProgram();
    program.bind();
    program.setUniform("lightDirection", transformedDirection);
    program.setUniform("lightColor", m_color);
    program.setUniform("lightAmbient", m_ambient);

    if (shadowMap) {
        program.setUniform("useShadowMap", true);
        program.setUniform("shadowMapViewProj", shadowMapViewProj);

        // We can't read depth textures with image-load-store, so bind to a sampler instead
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, shadowMap->texture());
    } else {
        program.setUniform("useShadowMap", false);
    }

    glBindImageTexture(0, target.texture(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
    glBindImageTexture(1, gbuffer.diffuseShininess().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
    glBindImageTexture(2, gbuffer.specular().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
    glBindImageTexture(3, gbuffer.normal().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
    glBindImageTexture(4, gbuffer.worldPos().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);

    glDispatchCompute((gbuffer.width() + 7) / 8, (gbuffer.height() + 7) / 8, 1);

    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}
