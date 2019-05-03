#include "ShadowDirectionalLight.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "RenderContext.h"
#include "CameraData.h"
#include "Math.h"
#include "defines.h"

using namespace Renderer;

ShadowDirectionalLight::ShadowDirectionalLight(Renderer::DirectionalLight baseLight, glm::vec3 pos, glm::vec3 up,
                                               glm::vec2 horizontalRange, glm::vec2 verticalRange, glm::vec2 depthRange,
                                               glm::uvec2 resolution, Renderer::RenderContext &renderContext)
    : m_renderContext(&renderContext),
      m_baseLight(baseLight),
      m_pos(pos),
      m_up(up),
      m_horizontalRange(horizontalRange),
      m_verticalRange(verticalRange),
      m_depthRange(depthRange),
      m_shadowMapFb(Framebuffer::textures(0, nullptr, &m_shadowMap)) {
    m_shadowMap.setSize(resolution.x, resolution.y);
}

void ShadowDirectionalLight::renderDebug(glm::mat4x4 transform) const {
    glm::vec3 _transformedPos, _transformedDirection;
    glm::mat4x4 shadowMapViewProj;
    getViewProjMatrix(transform, shadowMapViewProj, _transformedPos, _transformedDirection);

    m_renderContext->renderDebugFrustum(shadowMapViewProj);
}

void ShadowDirectionalLight::render(const Renderer::GBuffer &gbuffer, Renderer::ColorTexture &target,
                                    glm::mat4x4 transform, RenderLightGeometryCb &geometryCb) const {
    glm::vec3 transformedPos;
    glm::vec3 transformedDirection;
    glm::mat4x4 shadowMapViewProj;
    getViewProjMatrix(transform, shadowMapViewProj, transformedPos, transformedDirection);

    // Save the current camera state, since we'll need it when we invoke the light shader
    CameraBuffer originalCameraBuffer = m_renderContext->cameraData().state();

    // Render the geometry from the light's perspective into the shadow map
    m_renderContext->cameraData().setState(CameraBuffer(
        shadowMapViewProj,
        transformedPos,
        transformedDirection
    ));
    m_shadowMapFb.bind();
    glViewport(0, 0, m_shadowMap.width(), m_shadowMap.height());
    glClearDepth(0.f);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    geometryCb();
    glEnable(GL_CULL_FACE);

    // Reset the camera state to what is was before, since the light shader needs that data
    m_renderContext->cameraData().setState(originalCameraBuffer);

    // Render the directional light with the shadow map
    m_baseLight.renderWithShadowMap(gbuffer, target, &m_shadowMap, shadowMapViewProj, transform);
}

void ShadowDirectionalLight::getViewProjMatrix(glm::mat4x4 transform, glm::mat4x4 &out_viewProjMatrix,
                                               glm::vec3 &out_transformedPos,
                                               glm::vec3 &out_transformedDirection) const {
    out_transformedPos = transform * glm::vec4(m_pos.x, m_pos.y, m_pos.z, 1);
    out_transformedDirection = glm::normalize(glm::vec3(glm::transpose(glm::inverse(transform)) * glm::vec4(m_baseLight.direction().x, m_baseLight.direction().y, m_baseLight.direction().z, 0)));

    glm::mat4x4 viewMatrix = Math::viewMatrix(out_transformedPos, out_transformedDirection, m_up);
    glm::mat4x4 projMatrix = glm::ortho(
        m_horizontalRange.x, m_horizontalRange.y,
        m_verticalRange.x, m_verticalRange.y,
        m_depthRange.y, m_depthRange.x
    );
    out_viewProjMatrix = projMatrix * viewMatrix;
}
