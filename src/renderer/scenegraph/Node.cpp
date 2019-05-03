#include "Node.h"

using namespace Scenegraph;

Node::Node(glm::mat4x4 transform) : m_transform(transform) {}

glm::mat4x4 Node::absoluteTransform(const glm::mat4x4 &parentAbsTransform) const {
    return parentAbsTransform * m_transform;
}
