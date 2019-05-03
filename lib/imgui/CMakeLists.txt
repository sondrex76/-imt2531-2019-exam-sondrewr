set(SOURCE_FILES
      "${CMAKE_CURRENT_SOURCE_DIR}/imgui.h" "${CMAKE_CURRENT_SOURCE_DIR}/imgui.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/imconfig.h" "${CMAKE_CURRENT_SOURCE_DIR}/imgui_draw.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_glfw.h" "${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_glfw.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_opengl3.h" "${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_opengl3.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/imgui_internal.h" "${CMAKE_CURRENT_SOURCE_DIR}/imgui_widgets.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/imstb_rectpack.h" "${CMAKE_CURRENT_SOURCE_DIR}/imstb_truetype.h" 
      "${CMAKE_CURRENT_SOURCE_DIR}/imstb_textedit.h" )
      
target_sources(${PROJECT} PRIVATE ${SOURCE_FILES})