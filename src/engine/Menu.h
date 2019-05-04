#pragma once

// window
#include <GLFW/glfw3.h>

// imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void menuStatic(GLFWwindow& window);	// Runs static imGui code
void menuDynamic(bool &button);			// Runs dynamic imGui code
