#include "RenderContext.h"

#include "scenegraph/Node.h"

using namespace Renderer;

RenderContext::RenderContext()
    : m_geomProgram(ShaderProgram::vertexFragProgram("geometry.vert", "geometry.frag")),
      m_directionalLightProgram(ShaderProgram::computeProgram("directionalLight.compute")),
      m_spotLightProgram(ShaderProgram::computeProgram("spotLight.compute")),
      m_ambientLightProgram(ShaderProgram::computeProgram("ambientLight.compute")),

#ifdef RENDER_LIGHT_DEBUG
      m_debugFrustumLines(24, GL_ARRAY_BUFFER, GL_STATIC_DRAW),
      m_debugLightFrustum(ShaderProgram::vertexFragProgram("debug_lightFrustum.vert", "debug_lightFrustum.frag")),
#endif

      m_postDistanceFogProgram(ShaderProgram::computeProgram("post_distanceFog.compute")),
      m_postBloomExtractProgram(ShaderProgram::computeProgram("post_bloomExtract.compute")),
      m_postBloomBlurProgram(ShaderProgram::computeProgram("post_bloomBlur.compute")),
      m_postBloomCompositeProgram(ShaderProgram::computeProgram("post_bloomComposite.compute")),
      m_postGradingProgram(ShaderProgram::computeProgram("post_grading.compute")),
      m_renderToScreenProgram(ShaderProgram::vertexFragProgram("renderToScreen.vert", "renderToScreen.frag")),
      m_renderToScreenVertices(6, GL_ARRAY_BUFFER, GL_STATIC_DRAW) {
    // Set the material samplers to read from textures 0-3
    // This should match the texture units bound in Material::bind.
    m_geomProgram.setSampler("diffuseMap", 0);
    m_geomProgram.setSampler("specularMap", 1);
    m_geomProgram.setSampler("shininessMap", 2);
    m_geomProgram.setSampler("emissiveMap", 3);

    // Set the shadow map sampler to read from texture 0
    // This should match the texture unit bound in DirectionalLight::renderShadowMap.
    m_directionalLightProgram.setSampler("shadowMap", 0);

    m_renderToScreenProgram.setSampler("inTex", 0);

    static const glm::vec2 quadBufferData[] = {
        glm::vec2(0.f, 1.f),
        glm::vec2(1.f, 0.f),
        glm::vec2(0.f, 0.f),

        glm::vec2(1.f, 1.f),
        glm::vec2(1.f, 0.f),
        glm::vec2(0.f, 1.f)
    };
    m_renderToScreenArray.bind();
    m_renderToScreenVertices.upload(6, quadBufferData);
    m_renderToScreenArray.addAttrib(2, 2, 0);
    m_renderToScreenArray.unbind();

#ifdef RENDER_LIGHT_DEBUG
    static const glm::vec3 debugFrustumData[] = {
        glm::vec3(-1,  1,  1),
        glm::vec3(1,  1,  1),

        glm::vec3(1,  1,  1),
        glm::vec3(1, -1,  1),

        glm::vec3(1, -1,  1),
        glm::vec3(-1, -1,  1),

        glm::vec3(-1, -1,  1),
        glm::vec3(-1,  1,  1),


        glm::vec3(-1,  1, 0),
        glm::vec3(1,  1, 0),

        glm::vec3(1,  1, 0),
        glm::vec3(1, -1, 0),

        glm::vec3(1, -1, 0),
        glm::vec3(-1, -1, 0),

        glm::vec3(-1, -1, 0),
        glm::vec3(-1,  1, 0),


        glm::vec3(-1,  1,  1),
        glm::vec3(-1,  1, 0),

        glm::vec3(1,  1,  1),
        glm::vec3(1,  1, 0),

        glm::vec3(1, -1,  1),
        glm::vec3(1, -1, 0),

        glm::vec3(-1, -1,  1),
        glm::vec3(-1, -1, 0)
    };
    m_debugFrustumArray.bind();
    m_debugFrustumLines.upload(24, debugFrustumData);
    m_debugFrustumArray.addAttrib(3, 3, 0);
    m_debugFrustumArray.unbind();
#endif
}

void RenderContext::render(int screenWidth, int screenHeight, const Scenegraph::Node &node) {
    startRender(screenWidth, screenHeight);

    bindCamera(node);
    m_gbuffer.fb().bind();
    glViewport(0, 0, m_gbuffer.width(), m_gbuffer.height());
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClearDepth(0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderNodeGeometry(node);
    renderLights(node);
    renderPostEffects();
    renderToScreen();
}

void RenderContext::startRender(int screenWidth, int screenHeight) {
    m_gbuffer.setSize(screenWidth, screenHeight);
    m_bloomPingTarget.setSize(screenWidth, screenHeight);
    m_bloomPongTarget.setSize(screenWidth, screenHeight);
}

void RenderContext::bindCamera(const Scenegraph::Node &node) {
    node.bindActiveCamera(glm::mat4x4(1.f), m_cameraData);
    m_cameraData.bind();
}

void RenderContext::renderNodeGeometry(const Scenegraph::Node &node) {
    glEnable(GL_DEPTH_TEST);
    m_geomProgram.bind();
    node.renderGeometry(glm::mat4x4(1.f));
    glDisable(GL_DEPTH_TEST);
}

void RenderContext::renderLights(const Scenegraph::Node &node) {
    //glClearTexImage(m_lightTarget.texture(), 0, GL_RGBA, GL_FLOAT, nullptr);
    m_cameraData.bind();

    std::function<void()> renderGeomCallback = [this, &node]() {
        renderNodeGeometry(node);
    };
    node.renderLights(glm::mat4x4(1.f), m_gbuffer, m_gbuffer.emissive(), renderGeomCallback);
}

void RenderContext::renderPostEffects() {
    renderPostPass(m_postDistanceFogProgram);
    renderBloom();
    renderPostPass(m_postGradingProgram);
}

void RenderContext::renderToScreen() {
    m_renderToScreenArray.bind();
    m_renderToScreenProgram.bind();
    m_renderToScreenProgram.setUniform("viewportSize", glm::vec2(m_gbuffer.width(), m_gbuffer.height()));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.emissive().texture());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glViewport(0, 0, m_gbuffer.width(), m_gbuffer.height());
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void RenderContext::renderDebugFrustum(glm::mat4 frustumMatrix) {
#ifdef RENDER_LIGHT_DEBUG
    m_debugLightFrustum.bind();
    m_debugLightFrustum.setUniform("invLightMatrix", glm::inverse(frustumMatrix));
    m_debugFrustumArray.bind();
    m_debugFrustumLines.bind();
    glDrawArrays(GL_LINES, 0, m_debugFrustumLines.length());
    m_debugFrustumArray.unbind();
#endif
}

void RenderContext::renderPostPass(Renderer::ShaderProgram &program) {
    program.bind();
    program.setUniform("viewportSize", glm::vec2(m_gbuffer.width(), m_gbuffer.height()));
    glBindImageTexture(0, m_gbuffer.emissive().texture(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
    glBindImageTexture(1, m_gbuffer.diffuseShininess().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
    glBindImageTexture(2, m_gbuffer.normal().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
    glBindImageTexture(3, m_gbuffer.worldPos().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);

    dispatchPostPass();
}

void RenderContext::renderBloom() {
    // Extract the bright parts
    m_postBloomExtractProgram.bind();
    glBindImageTexture(0, m_gbuffer.emissive().texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
    glBindImageTexture(1, m_bloomPingTarget.texture(), 0, false, 0, GL_WRITE_ONLY, GL_RGBA32F);
    dispatchPostPass();

    // Blur the bright parts several times
    m_postBloomBlurProgram.bind();
    for (int i = 0; i < 10; i++) {
        // Blur horizontally
        m_postBloomBlurProgram.setUniform("direction", glm::ivec2(1, 0));
        glBindImageTexture(0, m_bloomPingTarget.texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
        glBindImageTexture(1, m_bloomPongTarget.texture(), 0, false, 0, GL_WRITE_ONLY, GL_RGBA32F);
        dispatchPostPass();

        // Blur vertically
        m_postBloomBlurProgram.setUniform("direction", glm::ivec2(0, 1));
        glBindImageTexture(0, m_bloomPongTarget.texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
        glBindImageTexture(1, m_bloomPingTarget.texture(), 0, false, 0, GL_WRITE_ONLY, GL_RGBA32F);
        dispatchPostPass();
    }

    // Composite the blurred image back on to the main image
    m_postBloomCompositeProgram.bind();
    glBindImageTexture(0, m_gbuffer.emissive().texture(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
    glBindImageTexture(1, m_bloomPingTarget.texture(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
    dispatchPostPass();
}

void RenderContext::dispatchPostPass() {
    glDispatchCompute((m_gbuffer.width() + 7) / 8, (m_gbuffer.height() + 7) / 8, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}
