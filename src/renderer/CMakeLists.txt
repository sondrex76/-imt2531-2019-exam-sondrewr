set(SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/AmbientLight.h" "${CMAKE_CURRENT_SOURCE_DIR}/AmbientLight.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Buffer.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/CameraData.h" "${CMAKE_CURRENT_SOURCE_DIR}/CameraData.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ColorTexture.h" "${CMAKE_CURRENT_SOURCE_DIR}/ColorTexture.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/defines.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/DepthStencilTexture.h" "${CMAKE_CURRENT_SOURCE_DIR}/DepthStencilTexture.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/DirectionalLight.h" "${CMAKE_CURRENT_SOURCE_DIR}/DirectionalLight.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ExtraMaterial.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Framebuffer.h" "${CMAKE_CURRENT_SOURCE_DIR}/Framebuffer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/GBuffer.h" "${CMAKE_CURRENT_SOURCE_DIR}/GBuffer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ImageTexture.h" "${CMAKE_CURRENT_SOURCE_DIR}/ImageTexture.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/LightCallback.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Material.h" "${CMAKE_CURRENT_SOURCE_DIR}/Material.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Math.h" "${CMAKE_CURRENT_SOURCE_DIR}/Math.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Mesh.h" "${CMAKE_CURRENT_SOURCE_DIR}/Mesh.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Model.h" "${CMAKE_CURRENT_SOURCE_DIR}/Model.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/RenderContext.h" "${CMAKE_CURRENT_SOURCE_DIR}/RenderContext.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.h" "${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ShadowDirectionalLight.h" "${CMAKE_CURRENT_SOURCE_DIR}/ShadowDirectionalLight.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/SpotLight.h" "${CMAKE_CURRENT_SOURCE_DIR}/SpotLight.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VertexAttribArray.h" "${CMAKE_CURRENT_SOURCE_DIR}/VertexAttribArray.cpp")
target_sources(${PROJECT} PRIVATE ${SOURCE_FILES})

add_subdirectory(scenegraph)
