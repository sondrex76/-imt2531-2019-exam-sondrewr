#include "AmbientLight.h"

#include "RenderContext.h"

using namespace Renderer;

AmbientLight::AmbientLight(glm::vec3 color, Renderer::RenderContext &renderContext)
    : m_renderContext(&renderContext), m_color(color) {}

void AmbientLight::render(const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target, glm::mat4x4 transform,
                          Renderer::RenderLightGeometryCb &geometryCb) const {
    ShaderProgram &program = m_renderContext->ambientLightProgram();
    program.bind();
    program.setUniform("lightColor", m_color);

    glBindImageTexture(0, target.texture(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
    glBindImageTexture(1, gbuffer.diffuseShininess().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);

    glDispatchCompute((gbuffer.width() + 7) / 8, (gbuffer.height() + 7) / 8, 1);

    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}
