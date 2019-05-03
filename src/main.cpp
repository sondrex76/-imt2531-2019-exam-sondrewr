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

#include "renderer/SpotLight.h"
#include "renderer/AmbientLight.h"

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
	Renderer::Model deerEye = Renderer::Model::fromObjFile("deerEyes/deer.obj", renderContext);
	Renderer::Model deerHead = Renderer::Model::fromObjFile("deerHead/deer.obj", renderContext);
	Renderer::Model deerBody = Renderer::Model::fromObjFile("deerBody/deer.obj", renderContext);

	// Sound
	// PlaySound("resources/Sound/<name of file>.wav", NULL, SND_LOOP | SND_ASYNC);

	// Mouse pos
	float previousMousePosX, previousMousePosY; // Previous mosePos

	// TimePassedValue, used to keep track of the position of the sun, the usn will likely gain its own class and this will be moved
	float timePassedValue = 0;


	// -- Geometry of terrain --

	std::vector<uint32_t> indices;						// indices
	std::vector<Renderer::Vertex> vertices;				// vector with vertexes

	// Number of indices
	int numIndices = 0;
	// Adds one for all elements up and left
	for (int i = 0; i < pow(SIZE_ENVIORMENT - 1, 2) * 6; i++) { // each loop adds one cube, which consists of two triangles
		indices.push_back(numIndices++);
	}

	// To have seperate colors, this needs to be split into a vector of models rather then a single one
	// Random in this case is deterministic based on the seed given
	int heights[SIZE_ENVIORMENT][SIZE_ENVIORMENT];	// Heightmap of map, all values should be a value form 0..255

	// TODO: Generate heightmap instead of having a set height
	for (int i = 0; i < SIZE_ENVIORMENT; i++) { // x
		for (int n = 0; n < SIZE_ENVIORMENT; n++) { // y
			heights[i][n] = 0; // temp heightmap generation
		}
	}

	int debugX = 0, debugY = 0;

	// Create vertevies based on heightmap
	for (int x = 0; x < SIZE_ENVIORMENT; x++) { // x
		for (int y = 0; y < SIZE_ENVIORMENT; y++) { // y
			// There is a point both to the right, down and across
			// This means triangles are to be generated based on the height map
			if (x + 1 < SIZE_ENVIORMENT && y + 1 < SIZE_ENVIORMENT) {
				// the vectors of the coordinates to be used
				glm::vec3 vectors[] = {
					glm::vec3(SIZE_TERRAIN * (x + 1), SIZE_TERRAIN * heights[x + 1][y + 1], SIZE_TERRAIN * (y + 1)),	// Upper/right triangle
					glm::vec3(SIZE_TERRAIN * (x + 1), SIZE_TERRAIN * heights[x + 1][y], SIZE_TERRAIN * y),
					glm::vec3(SIZE_TERRAIN * x, SIZE_TERRAIN * heights[x][y], SIZE_TERRAIN * y),

					glm::vec3(SIZE_TERRAIN * x, SIZE_TERRAIN * heights[x][y], SIZE_TERRAIN * y),						// Lower/left triangle
					glm::vec3(SIZE_TERRAIN * x, SIZE_TERRAIN * heights[x][y + 1], SIZE_TERRAIN * (y + 1)),
					glm::vec3(SIZE_TERRAIN * (x + 1), SIZE_TERRAIN * heights[x + 1][y + 1], SIZE_TERRAIN * (y + 1))
				};
				// Normal values
				glm::vec3 normal1 = getNormals(vectors[0], vectors[1], vectors[2]), normal2 = getNormals(vectors[3], vectors[4], vectors[5]);

				// Upper/right triangle
				vertices.push_back(Renderer::Vertex{ /*pos*/{vectors[0]}, /*norm*/normal1, /*uv*/{0.5, 0.5} });
				vertices.push_back(Renderer::Vertex{ /*pos*/{vectors[1]}, /*norm*/normal1, /*uv*/{0.5, 0.5} });
				vertices.push_back(Renderer::Vertex{ /*pos*/{vectors[2]}, /*norm*/normal1, /*uv*/{0.5, 0.5} });
				
				// Lower/left triangle
				vertices.push_back(Renderer::Vertex{ /*pos*/{vectors[3]}, /*norm*/normal2, /*uv*/{0.5, 0.5} });
				vertices.push_back(Renderer::Vertex{ /*pos*/{vectors[4]}, /*norm*/normal2, /*uv*/{0.5, 0.5} });
				vertices.push_back(Renderer::Vertex{ /*pos*/{vectors[5]}, /*norm*/normal2, /*uv*/{0.5, 0.5} });
				debugY++; 
			}
		}
	}

	// Generates material and actual terrain
	Renderer::Material terrainMaterial(Renderer::Material(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.8, 0.8, 0.8), 32.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
	Renderer::Model terrainGeometry = Renderer::Model::fromGeometry(&vertices[0], pow(SIZE_ENVIORMENT - 1, 2) * 3, &indices[0], indices.size(), std::move(terrainMaterial), renderContext);

	// Game loop
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		int windowWidth, windowHeight;
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

		// MousePos, could be useful for exam
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		previousMousePosX = xpos, previousMousePosY = ypos; // Updates values

		// Movement detection
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {			// W key, move forwards

		} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {	// A key, move left

		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {	// S key, move back
			
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {	// D key, move right

		}

		// x, y, z coordinates of camera and object
		glm::vec3 cameraPos = glm::vec3(0, 0., 500.);
		glm::vec3 objectPos = glm::vec3(0, 0, 0);		// Node position, changing this changes locaiton both of the object and of the camera

		// Angle towards car
		glm::vec4 angleToObject = glm::normalize(
			glm::vec4(cameraPos, 0)) * 
			glm::rotate(
				glm::mat4x4(1.f),																	// Identify matrix
				//0.0f,																				// Angle to rotate
				(float)((ypos - previousMousePosX) / 200.0f),										// Comment out the above and uncomment this to rotate camera around car again
				glm::vec3(0, 1, 0)																	// Defines the up direction
			);																
			
		// Scenegraph called node
		Scenegraph::GroupNode node(glm::translate(glm::mat4x4(1.f), objectPos));					// Primary node
		auto deerNode = std::make_unique<Scenegraph::GroupNode>(									// Node of deer
			glm::translate(
			glm::rotate(
				glm::scale(
					glm::mat4x4(1.f),				// Identity matrix
					glm::vec3(40.0f, 40.0f, 40.0f)	// Scale
				),
				(float)(90.f * M_PI / 180.f),		// Angle to rotate
				glm::vec3(0, 1, 0)					// Axis to rotate around
			),
			glm::vec3(1, 1, 1)						// Offset/Coordinates
			));	

		 // Render the terrain
		node.addNode(std::make_unique<Scenegraph::GeometryNode>(terrainGeometry, glm::scale(
			glm::mat4x4(1.f),				// Identity matrix
			glm::vec3(1.0f, 1.0f, 1.0f)		// Scale
		)));

		// Three deer models
		deerNode->addNode(std::make_unique<Scenegraph::GeometryNode>(deerHead, glm::mat4x4(1.f)));
		deerNode->addNode(std::make_unique<Scenegraph::GeometryNode>(deerEye, glm::mat4x4(1.f)));
		deerNode->addNode(std::make_unique<Scenegraph::GeometryNode>(deerBody, glm::mat4x4(1.f)));

		node.addNode(std::move(deerNode)); // move because it is put into a variable first

		// Camera, remember: x, z is the horizontal plane, y is the vertical
		node.addNode(std::make_unique<Scenegraph::PerspectiveCameraNode>(						// Camera
			glm::vec3(0, 100, 500),																// pos
			angleToObject,																		// forward
			glm::vec3(0., 1., 0.),                     											// up
			45.f * M_PI / 180.f,                                      							// fov
			(float)windowWidth / (float)windowHeight, 											// aspect
			0.01f,                                     											// near z
			20000.f                                     										// far z
			));

		// Ambient light
		node.addNode(std::make_unique<Scenegraph::LightNode<Renderer::AmbientLight>>(
			Renderer::AmbientLight(glm::vec3(0.04, 0.04, 0.02), renderContext), glm::mat4x4(1.f)
			));

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
