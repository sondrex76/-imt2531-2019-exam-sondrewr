#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "Buffer.h"

namespace Renderer {

    class CameraBuffer {
    public:
        glm::mat4x4 viewProjMatrix;
        glm::mat4x4 invViewProjMatrix;
        glm::vec3 position;
        float _pad0;
        glm::vec3 direction;
        float _pad1;

        CameraBuffer() {}
        CameraBuffer(glm::mat4x4 viewProjMatrix, glm::vec3 position, glm::vec3 direction)
            : viewProjMatrix(viewProjMatrix),
              invViewProjMatrix(glm::inverse(viewProjMatrix)),
              position(position),
              _pad0(0),
              direction(direction),
              _pad1(0) {}
    };

    class CameraData {
    public:
        CameraData();

        void setState(CameraBuffer newBuffer);

        void bind() const;

        const CameraBuffer &state() const { return m_currentState; }

        const Buffer<CameraBuffer> &buffer() const { return m_gpuState; }

    private:
        CameraBuffer m_currentState;
        Buffer<CameraBuffer> m_gpuState;
    };

}
