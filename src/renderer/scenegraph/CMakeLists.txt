set(SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/CustomNode.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/GeometryNode.h" "${CMAKE_CURRENT_SOURCE_DIR}/GeometryNode.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/GroupNode.h" "${CMAKE_CURRENT_SOURCE_DIR}/GroupNode.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/LightNode.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Node.h" "${CMAKE_CURRENT_SOURCE_DIR}/Node.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/PerspectiveCameraNode.h" "${CMAKE_CURRENT_SOURCE_DIR}/PerspectiveCameraNode.cpp")

target_sources(${PROJECT} PRIVATE ${SOURCE_FILES})
