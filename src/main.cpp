#define GFX_NO_TERMINATION_ON_GL_ERROR
#define GFX_IMPLEMENTATION
#include <GFX/gfx.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <random>

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
#include "engine/PerlinNoise.h"
#include "engine/Menu.h"
#include "engine/Weather.h"

#include "renderer/SpotLight.h"
#include "renderer/AmbientLight.h"


float globalGradient[SIZE_ZONES][SIZE_ZONES][2];					// Global values of gradiant
bool moving[6] = { false, false, false, false, false, false };		// Bools indicating if the movement buttons are clicked

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
	GFX_GL_CALL(glClearColor(0, 0, 0.5, 1));					// Sets the rendering color to black
	GFX_GL_CALL(glEnable(GL_CULL_FACE));						// 
	GFX_GL_CALL(glFrontFace(GL_CW));							// 
	GFX_GL_CALL(glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE));	// 
	GFX_GL_CALL(glDepthFunc(GL_GREATER));						// 

	// Context of rendering
	Renderer::RenderContext renderContext;

	// Models
	Renderer::Model deer = Renderer::Model::fromObjFile("deer/deer.obj", renderContext);

	// Sound
	// PlaySound("resources/Sound/<name of file>.wav", NULL, SND_LOOP | SND_ASYNC);

	// Sun
	Renderer::ShadowDirectionalLight sunLight(
		Renderer::DirectionalLight(
			glm::normalize(glm::vec3(0, 0.5, 1)),	// Direction
			SUN_LIGHT_COLOR,						// Color
			0,
			renderContext
		),
		glm::vec3(0, 0, 4000),
		glm::vec3(0, 1, 0),

		glm::vec2(-780, 780),
		glm::vec2(0, 4000),
		glm::vec2(0, 11000),

		glm::uvec2(4096, 4096),
		renderContext
	);

	// -- Geometry of terrain --
	std::vector<uint32_t> indices;						// indices
	std::vector<Renderer::Vertex> vertices;				// vector with vertexes

	// Adds one for all elements up and left
	for (int numIndices = 0; numIndices < pow(SIZE_ENVIORMENT - 1, 2) * 6; numIndices++) { // each loop adds one cube, which consists of two triangles
		indices.push_back(numIndices);
	}

	// To have seperate colors, this needs to be split into a vector of models rather then a single one
	// Random in this case is deterministic based on the seed given
	int heights[SIZE_ENVIORMENT][SIZE_ENVIORMENT];	// Heightmap of map, all values should be a value form 0..255

	// Random number generator
	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0, MAX_HEIGHT);
	std::uniform_int_distribution<int> snowLocation(0, DIST_SNOW_SPAWN);	// distribution(snowLocation) returns an int between 0 and DIST_SNOW_SPAWN
	
	for (int i = 0; i < SIZE_ZONES; i++) {
		for (int n = 0; n < SIZE_ZONES; n++) {
			globalGradient[i][n][0] = distribution(generator);
			globalGradient[i][n][1] = distribution(generator);
			/*
			if (i < SIZE_ZONES || n > SIZE_ZONES && i > SIZE_ZONES) // Attempt at making the terrain decrease in height at certain points
				globalGradient[i][n][1] /= 2; 
			else
				globalGradient[i][n][1] = distribution(generator);
				*/
		}
	}

	// Generates map through perlin noise
	for (int i = 0; i < SIZE_ENVIORMENT; i++) { // x
		for (int n = 0; n < SIZE_ENVIORMENT; n++) { // y
			heights[i][n] = perlin((float)i / SIZE_DIVIDER, (float)n / SIZE_DIVIDER);
			if (heights[i][n] <= MAX_HEIGHT * HEIGHT_STAGES[0]) // Sea level
				heights[i][n] = MAX_HEIGHT * HEIGHT_STAGES[0];
		}
	}

	// Create vertevies based on heightmap
	for (int x = 0; x < SIZE_ENVIORMENT; x++) { // x
		for (int y = 0; y < SIZE_ENVIORMENT; y++) { // y
			// There is a point both to the right, down and across
			// This means triangles are to be generated based on the height map
			if (x + 1 < SIZE_ENVIORMENT && y + 1 < SIZE_ENVIORMENT) {
				// the vectors of the coordinates to be used
				glm::vec3 vectors[] = {
					glm::vec3(SIZE_TERRAIN * (x + 1), HEIGHT_TERRAIN * SIZE_TERRAIN * heights[x + 1][y + 1], SIZE_TERRAIN * (y + 1)),	// Upper/right triangle
					glm::vec3(SIZE_TERRAIN * (x + 1),  HEIGHT_TERRAIN * SIZE_TERRAIN * heights[x + 1][y], SIZE_TERRAIN * y),
					glm::vec3(SIZE_TERRAIN * x,  HEIGHT_TERRAIN * SIZE_TERRAIN * heights[x][y], SIZE_TERRAIN * y),
					glm::vec3(SIZE_TERRAIN * x,  HEIGHT_TERRAIN * SIZE_TERRAIN * heights[x][y + 1], SIZE_TERRAIN * (y + 1))
				};
				// Normal values
				glm::vec3 normal1 = getNormals(vectors[0], vectors[1], vectors[2]), normal2 = getNormals(vectors[2], vectors[3], vectors[0]);

				float height = getHeight(vectors[0], vectors[1], vectors[2]);
				glm::vec2 uvOffset = textureOffset(height);						// uv offset
					// Upper/right triangle
					vertices.push_back(Renderer::Vertex{ /*pos*/{vectors[0]}, /*norm*/normal1, /*uv*/{0 + uvOffset.x, 0 + uvOffset.y} });
					vertices.push_back(Renderer::Vertex{ /*pos*/{vectors[1]}, /*norm*/normal1, /*uv*/{0 + uvOffset.x, 1 + uvOffset.y} });
					vertices.push_back(Renderer::Vertex{ /*pos*/{vectors[2]}, /*norm*/normal1, /*uv*/{0.2 + uvOffset.x, 1 + uvOffset.y} });

					height = getHeight(vectors[2], vectors[3], vectors[0]);
					uvOffset = textureOffset(height);								// uv offset

					// Lower/left triangle
					vertices.push_back(Renderer::Vertex{ /*pos*/{vectors[2]}, /*norm*/normal2, /*uv*/{0.2 + uvOffset.x, 1 + uvOffset.y} });
					vertices.push_back(Renderer::Vertex{ /*pos*/{vectors[3]}, /*norm*/normal2, /*uv*/{0.2 + uvOffset.x, 0 + uvOffset.y} });
					vertices.push_back(Renderer::Vertex{ /*pos*/{vectors[0]}, /*norm*/normal2, /*uv*/{0 + uvOffset.x, 0 + uvOffset.y} });
			}
		}
	}

	// renders ground texture
	Renderer::ImageTexture textures(Renderer::ImageTexture::fromFile("resources/Textures/Ground.png"));

	// fromFile on the diffuse, and fromColor on all the other ones
	// Renderer::Material terrainMaterial(Renderer::Material(std::move(stuff1), std::move(stuff2), std::move(stuff3), std::move(stuff4))); // OLD
	Renderer::Material terrainMaterial(Renderer::Material(std::move(textures), glm::vec3(0.01, 0.01, 0.01), 32.0f, glm::vec3(0, 0, 0)));

	// Generates material and actual terrain
	Renderer::Model terrainGeometry = Renderer::Model::fromGeometry(&vertices[0], pow(SIZE_ENVIORMENT - 1, 2) * 6, &indices[0], indices.size(), std::move(terrainMaterial), renderContext);

	std::vector<Renderer::SpotLight> lights; // vector of lights placed by user

	// snowflakeDegrees.erase(snowflakeDegrees.begin() + n);	// Remove element at position n
	std::vector<Snowflake> snowflakes;							// Vector of snowflakes
	// Renderer::Model snowflakeTestModel = (Snowflake(glm::vec3(0, 100, 0), glm::vec3(0, 0, 0))).returnSnowflake(indices, std::move(snowflakeMaterial), renderContext);

	// Mouse pos
	float previousMousePosX = 0, previousMousePosY = 0; // Previous mosePos
	float cameraPosX = 0, cameraPosY = 0;				// Camera values to keep track of camera
	glm::vec3 cameraCordsOffset(0, 100, 50);			// Camera offset in coordinates

	// imGui static
	menuStatic(*window);

	// time
	std::chrono::milliseconds ms;

	ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		);

	// Time values, stores the old and current times, in addition to the difference
	long long oldTime = ms.count(), newTime, timeSpent;

	Renderer::Model snowModel = getSnowModel(renderContext);

	// Snow timer
	int snowTimer = 0;								// Time until snow should spawn
	glm::vec3 deerPosition = glm::vec3(0, 0, 0);	// Deer
	float angleDown = 0;							// Initial angle downwards
	camera currentCamera = freeCamera;				// Current camera type
	long long timeCameraSwitched = 0;				// The last time the camera mode switched

	// Game loop
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
			);
		newTime = ms.count();			// Updates newTime
		timeSpent = newTime - oldTime;	// Gets time value

		menuDynamic();					// dynamic imGUI
		updateCords(cameraCordsOffset);	// Updates coordinates
		bool placeLightNode = placeLight();	// Checks if light should be placed

		int windowWidth, windowHeight;
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

		// MousePos, gets mouse x and y pos
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if (!previousMousePosX)
			previousMousePosX = xpos;
		if (!previousMousePosY)
			previousMousePosY = ypos;

		// switch camera mode
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {			// A key, move left
			if (timeCameraSwitched + MIN_TIME_CAMERA < newTime) {	// Checks if enough time have passed
				timeCameraSwitched = newTime;

				std::cout << newTime << std::endl;

				if (currentCamera == freeCamera)
					currentCamera = firstCamera;
				else if (currentCamera == firstCamera)
					currentCamera = thirdCamera;
				else
					currentCamera = freeCamera;
			}
		}

		// x, y, z coordinates of camera and object
		glm::vec3 cameraPos = glm::vec3(0, 0., 50.);
		glm::vec3 objectPos = glm::vec3(0, 0, 0);		// Node position, changing this changes locaiton both of the object and of the camera
			
		// Scenegraph called node
		Scenegraph::GroupNode node(glm::translate(glm::mat4x4(1.f), objectPos));					// Primary node
		auto deerNode = std::make_unique<Scenegraph::GroupNode>(									// Node of deer
			glm::translate(
			glm::rotate(
				glm::scale(
					glm::mat4x4(1.f),								// Identity matrix
					glm::vec3(DEER_SCALE, DEER_SCALE, DEER_SCALE)	// Scale
				),
				(float)(90.f * M_PI / 180.f),						// Angle to rotate
				glm::vec3(0, 1, 0)									// Axis to rotate around
			),
			deerPosition					// Offset/Coordinates
			));	

		// Generates snowflakes
		snowTimer -= timeSpent;
		// Spawns snowwhen snowTimer is smaller then 0 and adds waiting time to the waiting
		for (; snowTimer < 0; snowTimer += WAIT_TIME_SNOW) {
			glm::vec2 location = glm::vec2(snowLocation(generator), snowLocation(generator)); // Gets grid location of snow

			if (validLocation(cameraCordsOffset.x / 2 + location.x) && validLocation(cameraCordsOffset.z / 2 + location.y))
			{
				snowflakes.push_back(Snowflake(glm::vec3((cameraCordsOffset.x / 2 + location.x), SNOW_SPAWN_HEIGHT, (cameraCordsOffset.z / 2 + location.y)), glm::vec3(0, 1, 0)));
			}
		}

		for (int i = 0; i < snowflakes.size(); i++) { // Goes through all current snowflakes
			snowflakes[i].moveSnowflake(timeSpent); // Updates position

			if (snowflakes[i].returnHeight() < heights[(int)(snowflakes[i].returnX() / SIZE_TERRAIN)][(int)(snowflakes[i].returnZ() / SIZE_TERRAIN)]) { // Checks if snowflake should be deleted
				snowflakes.erase(snowflakes.begin() + i);
				i--;
			}
			else { // Render model
				snowflakes[i].renderSnowflake(node, snowModel);
			}
		}

		 // Render the terrain
		node.addNode(std::make_unique<Scenegraph::GeometryNode>(terrainGeometry, glm::scale(
			glm::mat4x4(1.f),				// Identity matrix
			glm::vec3(1.0f, 1.0f, 1.0f)		// Scale
		)));

		// Deer model, it is in its own node because previouly it was split into three models
		deerNode->addNode(std::make_unique<Scenegraph::GeometryNode>(deer, glm::mat4x4(1.f)));

		node.addNode(std::move(deerNode));
		
		// Camera

		glm::vec3 movementVector = glm::vec3(0, 0, 0); // vector for how much the camera should move

		// Check what camera mode is being used
		if (currentCamera == freeCamera) {										// Free camera movement
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {					// W key, move forwards
				movementVector.z += timeSpent * DEER_SPEED;
			}
			else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {			// S key, move back
				movementVector.z -= timeSpent * DEER_SPEED;
			}

			// Movement left, right
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {					// A key, move left
				movementVector.x -= timeSpent * DEER_SPEED;
			}
			else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {			// D key, move right
				movementVector.x += timeSpent * DEER_SPEED;
			}

			// Up/down
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {				// Space key, move up
				movementVector.x -= timeSpent * DEER_SPEED;
			}
			else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {	// Shift, downwards
				movementVector.x += timeSpent * DEER_SPEED;
			}
		}
		else {	// third and first camera
			// Movement forwards, backwards
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {					// W key, move forwards
				movementVector.z += timeSpent * DEER_SPEED;
			}
			else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {			// S key, move back
				movementVector.z -= timeSpent * DEER_SPEED;
			}

			// Movement left, right
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {					// A key, move left
				movementVector.x -= timeSpent * DEER_SPEED;
			}
			else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {			// D key, move right
				movementVector.x += timeSpent * DEER_SPEED;
			}
		}

		angleDown += (float)((ypos - previousMousePosY) * SENSITIVITY);

		if (angleDown < -MAX_ANGLE_VERTICAL)
			angleDown = -MAX_ANGLE_VERTICAL;
		else if (angleDown > MAX_ANGLE_VERTICAL)
			angleDown = MAX_ANGLE_VERTICAL;

		// Angle towards object
		glm::vec4 angle = glm::normalize(
			glm::vec4(cameraPos, 0) * 
			glm::rotate(																			// Horizontal
				glm::mat4x4(1.f),																	// Identify matrix
				angleDown,																			// Angle to rotate
				glm::normalize(glm::vec3(1, 0, 1))													// Defines the up direction
			) *
			glm::rotate(																			// Vertical
				glm::mat4x4(1.f),																	// Identify matrix
				(float)((previousMousePosX - xpos) * SENSITIVITY),									// Angle to rotate
				glm::vec3(0, 1, 0)																	// Defines the up direction
			));

		// Places new light into vector
		if (placeLightNode) {
			lights.push_back(
				Renderer::SpotLight( // the vector vec4(1, 1, 1, 1) is incorrect, figure out how to get vector from matrix
					cameraCordsOffset + (glm::vec3)angle * DISTANCE_LIGHT_SPAWN,
					glm::vec3(0, 0, 0),				// direction
					glm::vec3(1, 1, 1),				// Color
					(float)(360.f * M_PI / 180.f),	// cutoffRadians
					10.0f,							// focus
					1.0f,							// ambient
					25.0f,							// radius
					0.01f,							// falloff
					renderContext					// renderContext
				)
			);
		}

		// std::vector<Scenegraph::LightNode<Renderer::SpotLight>> lights;
		// Draw all lights inside of the lights vector
		for (int i = 0; i < lights.size(); i++) {
			node.addNode(std::make_unique<Scenegraph::LightNode<Renderer::SpotLight>>(
				Renderer::SpotLight(lights[i]), glm::mat4x4(1.f)
				)
			);
		}

		// Camera, remember: x, z is the horizontal plane, y is the vertical
		node.addNode(std::make_unique<Scenegraph::PerspectiveCameraNode>(						// Camera
			cameraCordsOffset,																	// pos
			angle,																				// forward
			glm::vec3(0., 1., 0.),                     											// up
			60.f * M_PI / 180.f,                                      							// fov
			(float)windowWidth / (float)windowHeight, 											// aspect
			0.01f,                                     											// near z
			20000.f                                     										// far z
			));

		
		// Ambient light
		node.addNode(std::make_unique<Scenegraph::LightNode<Renderer::AmbientLight>>(
			Renderer::AmbientLight(PASSIVE_LIGHT_COLOR, renderContext), glm::mat4x4(1.f)
			));
			
		node.addNode(std::make_unique<Scenegraph::LightNode<Renderer::ShadowDirectionalLight>>(
			sunLight,
			glm::mat4x4(1.f)
			));

		renderContext.render(windowWidth, windowHeight, node);

		// Render ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();

		// Updates mouse Pos coordinates
		// previousMousePosX = xpos;
		previousMousePosY = ypos; 
		oldTime = newTime;	//		 Updates oldTime
	}

	glfwDestroyWindow(window);
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int nCmdShow) {
	return main();
}
