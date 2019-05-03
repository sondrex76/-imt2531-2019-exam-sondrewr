#include "CameraData.h"

using namespace Renderer;

CameraData::CameraData() : m_gpuState(1, GL_UNIFORM_BUFFER, GL_DYNAMIC_DRAW) {}

void CameraData::setState(Renderer::CameraBuffer newBuffer) {
    m_currentState = newBuffer;
    *m_gpuState.map().items() = newBuffer;
}

void CameraData::bind() const {
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_gpuState.buffer());
}
