cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

# Set the project name to be the name of the folder that holds the source code
get_filename_component(PROJECT ${CMAKE_SOURCE_DIR} NAME)
project(Exam-imt2531-2019)

# Aliases
set(ROOT   ${CMAKE_SOURCE_DIR})
set(SRCDIR ${CMAKE_SOURCE_DIR}/src)
set(LIBDIR ${CMAKE_SOURCE_DIR}/lib)
set(RESDIR ${CMAKE_SOURCE_DIR}/resources)
set(BINDIR ${CMAKE_BINARY_DIR})

set(COPY_SILENT ON)

# Define executeables by entrypoint
add_executable(${PROJECT} "src/main.cpp")

set_target_properties( ${PROJECT}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY "${BINDIR}"
    RUNTIME_BINARY_DIRECTORY "${BINDIR}/bin"
	#LINK_FLAGS "/SUBSYSTEM:WINDOWS"
)

# Find system packages
find_package(OpenGL REQUIRED)
if(NOT MSVC)
    find_package(GLEW REQUIRED)
endif()

# Turning off parts of GLFW we do not want to build
set(GLFW_BUILD_EXAMPLES 0)
set(GLFW_BUILD_TESTS 0)
set(GLFW_BUILD_DOCS 0)

# Adding subdirectory, building the glfw library which we will link to later on.
add_subdirectory("${LIBDIR}/glfw/")

#ASSIMP

message(STATUS "Assimp not installed. Compiling from source.")
set(ASSIMP_BUILD_ASSIMP_TOOLS 0)
unset(ASSIMP_LIBRARY_SUFFIX CACHE)
add_subdirectory ("${LIBDIR}/assimp")
find_package(assimp)
set(ASSIMP_INCLUDE_DIRS "${LIBDIR}/assimp/include/" "${BINDIR}/lib/assimp/include/")
set(ASSIMP_LIBRARY_DIRS "${BINDIR}/lib")
#set(ASSIMP_INCLUDE_DIRS "${BINDIR}/lib/assimp/include" "${LIBDIR}/assimp/include")

# Set up directories from which you can #include
include_directories(
		${LIBDIR}
		${LIBDIR}/glew/include
		${LIBDIR}/glm
		${LIBDIR}/glfw/include
		${LIBDIR}/stb
        ${LIBDIR}/imgui
		${ASSIMP_INCLUDE_DIRS}
)

add_subdirectory(src/renderer)
add_subdirectory(src/engine)
add_subdirectory(lib/imgui)

# enlist all the resources already in the build directory
file(GLOB_RECURSE OLD_RESOURCES
	LIST_DIRECTORIES true	# also list directories
	${BINDIR}/resources/*   # the pattern to look for. * is a wildcard
)
 # remove all the old resources
if(DEFINED OLD_RESOURCES AND NOT OLD_RESOURCES STREQUAL "")
	file(REMOVE_RECURSE ${OLD_RESOURCES})
endif()
# enlist all the runtime resources (i.e. the ones in the source directory)
file(GLOB_RECURSE ALL_RESOURCES
	RELATIVE ${RESDIR}	# format the output paths relative to RESDIR
	resources/*			# the pattern to look for. * is a wildcard
)
if (COPY_SILENT)
	message("Copying files:  ${RESDIR}/<files...>  -> ${BINDIR}/resources/<files...>")
endif()
foreach(file ${ALL_RESOURCES})
    if (NOT COPY_SILENT)
		message("Copy file:  ${RESDIR}/${file}  -> ${BINDIR}/resources/${file}")
	endif()
	# using configure_file instread of file(COPY ...) because we want it to happen every time we build
    configure_file( ${RESDIR}/${file} ${BINDIR}/resources/${file} COPYONLY)
endforeach(file)

#########################################
# Microsoft Visual studio 2017 (Windows)
#########################################
if(MSVC)
	# NOTE: if you find a nicer way to detect build configuration, please notify us on discord or gitlab!
	# Find the libraries matching build configuration: 4 => Win32, 8 => x64
	if( ${CMAKE_SIZEOF_VOID_P} EQUAL 4)
	# Win32 configuration
		#declare where to find glew32.lib
		set(GLEW_LIBRARY ${LIBDIR}/glew/lib/Release/Win32/glew32.lib)
		# Copy these files in order to allow windows to link your executeables
		file(COPY ${LIBDIR}/glew/bin/Release/Win32/glew32.dll DESTINATION ${BINDIR})
	else()
	# x64 configuration
		set(GLEW_LIBRARY ${LIBDIR}/glew/lib/Release/x64/glew32.lib)
		file(COPY ${LIBDIR}/glew/bin/Release/x64/glew32.dll DESTINATION ${BINDIR})
	endif()
else()
#########################################
# Apple, linux, others...
#########################################
	target_compile_options(
	    ${PROJECT}
	    PRIVATE "-Wall"
	    PRIVATE "-Wextra"
	    PRIVATE "-g"
	    PRIVATE "-std=c++17"
	)
endif()
message("ASSIMP_LIBRARY_DIRS: ${ASSIMP_LIBRARY_DIRS}")
message("ASSIMP_LIBRARIES: ${ASSIMP_LIBRARIES}")

link_directories(${ASSIMP_LIBRARY_DIRS}/assimp/code/)

target_link_libraries(
    ${PROJECT}
    PRIVATE ${OPENGL_LIBRARIES}
    PRIVATE ${GLEW_LIBRARY}
    PRIVATE glfw
    PRIVATE assimp
)
message("CMake configured ${PROJECT} successfully!")
