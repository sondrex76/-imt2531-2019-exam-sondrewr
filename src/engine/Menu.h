#pragma once

// window
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "consts.h"

void menuStatic(GLFWwindow& window);			// Runs static imGui code
ImGuiWindowFlags runFlags();					// Runs flags
void menuDynamic();								// Runs dynamic imGui code
void updateCords(glm::vec3& CameraCordsOffset);	// Updates coordinates based on 
bool placeLight();								// Checks if a light should be placed