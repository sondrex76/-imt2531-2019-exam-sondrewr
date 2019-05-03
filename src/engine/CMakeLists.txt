set(SOURCE_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/Functions.h" "${CMAKE_CURRENT_SOURCE_DIR}/Functions.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Enviorment.h" "${CMAKE_CURRENT_SOURCE_DIR}/Enviorment.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/CubeVertex.h")
		

target_sources(${PROJECT} PRIVATE ${SOURCE_FILES})