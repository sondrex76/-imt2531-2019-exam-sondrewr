#define GFX_NO_TERMINATION_ON_GL_ERROR
#define GFX_IMPLEMENTATION
#include <GFX/gfx.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <fstream>

// Sound
// #include <Windows.h>
// #pragma comment(lib, "winmm.lib")

#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>

#include "renderer/RenderContext.h"
#include "renderer/Model.h"
#include "renderer/DirectionalLight.h"
#include "renderer/ShadowDirectionalLight.h"
#include "renderer/scenegraph/GroupNode.h"
#include "renderer/scenegraph/GeometryNode.h"
#include "renderer/scenegraph/PerspectiveCameraNode.h"
#include "renderer/scenegraph/LightNode.h"
#include "renderer/scenegraph/CustomNode.h"

#include "engine/consts.h"
#include "engine/Functions.h"
#include "engine/CubeVertex.h"

#include "renderer/SpotLight.h"
#include "renderer/AmbientLight.h"

// Fragment shaders are run on each pixel which is filled by a poligon
// Vertex shaders are applied to each vertex, So normally they take in a 3D position(the vertex pos) and camera data(view and projection matrices) and convert that position into "clip space"(screen actual position basically).

int main() {
	if (!glfwInit()) {
		GFX_ERROR("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_SAMPLES, 1);								// Enambles multisampling(anti-aliasing)
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);						// Allows the window to be resizable
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);					// Specifies the major openGL version as 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);					// Specifies the minor openGL version as 5
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);			// Devices with a newer version may work, its a setting
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// Use all the call functions, load this version of OpenGl and nothing else

	// Creates window, or on a fail it instead terminates
	auto window = glfwCreateWindow(1280, 720, "ARFRD", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		GFX_ERROR("Failed to create a GLFW window");
	}

	// Checks if GLEW is ok
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		GFX_ERROR("Failed to initialize GLEW");
	}

	// rendering stuff
	GFX_GL_CALL(glClearColor(0, 0, 0, 1));						// Sets the rendering color to black
	GFX_GL_CALL(glEnable(GL_CULL_FACE));						// 
	GFX_GL_CALL(glFrontFace(GL_CW));							// 
	GFX_GL_CALL(glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE));	// 
	GFX_GL_CALL(glDepthFunc(GL_GREATER));						// 

	// Context of rendering
	Renderer::RenderContext renderContext;

	// Models
	Renderer::Model deerModel = Renderer::Model::fromObjFile("deer/deer.obj", renderContext);

	// Sound
	// PlaySound("resources/Sound/<name of file>.wav", NULL, SND_LOOP | SND_ASYNC);

	// Mouse pos
	float previousMousePosX, previousMousePosY; // Previous mosePos

	// TimePassedValue, value used to increase road and note speed, WIP, currently does nothing
	float timePassedValue = 0;

	// Custom shape
	std::vector<uint32_t> cubeIndices;
	for (int i = 0; i < 36; i++)
		cubeIndices.push_back(i);

	Renderer::Material cubeMaterial = Renderer::Material(glm::vec3(0, 1, 1), 1.0f, 1.0f, glm::vec3(1, 0, 1));
	Renderer::Model cube = Renderer::Model::fromGeometry(vertices, 36, &cubeIndices[0], cubeIndices.size(), std::move(cubeMaterial), renderContext);



	// Game loop
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

		int windowWidth, windowHeight;
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

		// MousePos, could be useful for exam
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		previousMousePosX = xpos, previousMousePosY = ypos; // Updates values

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {   // D key, move right

		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {  // A key, move left

		}

		// x, y, z coordinates of camera and object
		glm::vec3 cameraPos = glm::vec3(0, 0., 500.);
		glm::vec3 objectPos = glm::vec3(0, 0, 0);		// Node position, changing this changes locaiton both of the object and of the camera

		// Angle towards car
		glm::vec4 angleToObject = glm::normalize(
			glm::vec4(cameraPos, 0)) * 
			glm::rotate(
				glm::mat4x4(1.f),																	// Identify matrix
				0.0f,																				// Angle to rotate
				//(float)((ypos - previousMousePosX) / 200.0f),										// Comment out the above and uncomment this to rotate camera around car again
				glm::vec3(0, 1, 0)																	// Defines the up direction
			);																
			
		// node
		Scenegraph::GroupNode node(glm::translate(glm::mat4x4(1.f), objectPos));

		// Order: transformation, Rotation, Scale

		// testModel, glm::vec3(1, 1, 1) is the coordinates of the model itself
			// node.addNode(std::make_unique<Scenegraph::GeometryNode>(Renderer::Model, glm::translate(glm::scale(glm::mat4x4(1.f), glm::vec3(scale, scale, scale)), glm::vec3(xCordsOfModel, yCordsOfModel, zCordsOfModel))));
		/*
		node.addNode(std::make_unique<Scenegraph::GeometryNode>(testModel, glm::translate(glm::scale(glm::mat4x4(1.f), glm::vec3(1.2f, 1.2f, 1.2f)), glm::vec3(0, 0, 0))));
		node.addNode(std::make_unique<Scenegraph::GeometryNode>(
			cityModel, 
			glm::translate(
				glm::rotate(
					glm::scale(
						glm::mat4x4(1.f),			// Identity matrix
						glm::vec3(0.2f, 0.2f, 0.2f) // Scale
					), 
					0.6f,							// Angle to rotate
					glm::vec3(1, 0, 0)				// Axis to rotate around
				), 
				glm::vec3(1, 1, 1)					// Offset/Coordinates
			)
			)); */

		// group
		// When moving node into other node, do whatever you want with it before moving it into another group, as it becoems invalid afterwards

		// Scenegraph::GroupNode node2(glm::translate(glm::mat4x4(1.f), objectPos)); // This becoems the line below
		auto node2 = std::make_unique<Scenegraph::GroupNode>(glm::translate(glm::mat4x4(1.f), objectPos));
		node.addNode(std::move(node2)); // move because it is put into a variable first
		// node.addNode(std::make_unique<Scenegraph::GroupNode>(glm::translate(glm::mat4x4(1.f), objectPos))); // This would also work
		

		// x, z is the horizontal plane, y is the vertical

		// Camera
		node.addNode(std::make_unique<Scenegraph::PerspectiveCameraNode>(						// Camera
			glm::vec3(0, 100, 500),																// pos
			angleToObject,																		// forward
			glm::vec3(0., 1., 0.),                     											// up
			45.f * M_PI / 180.f,                                      							// fov
			(float)windowWidth / (float)windowHeight, 											// aspect
			0.01f,                                     											// near z
			20000.f                                     										// far z
			));

		// Ambient light, can probably be removed
		node.addNode(std::make_unique<Scenegraph::LightNode<Renderer::AmbientLight>>(
			Renderer::AmbientLight(glm::vec3(0.02, 0.001, 0.1), renderContext), glm::mat4x4(1.f)
			));

		node.addNode(std::make_unique<Scenegraph::GeometryNode>(cube, glm::scale(
			glm::mat4x4(1.f),			// Identity matrix
			glm::vec3(12.0f, 12.0f, 12.0f) // Scale
		)));

		renderContext.render(windowWidth, windowHeight, node);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int nCmdShow) {
	return main();
}
