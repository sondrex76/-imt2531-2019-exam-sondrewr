#pragma once

// window
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "consts.h"

void menuStatic(GLFWwindow& window);	// Runs static imGui code
void menuDynamic();						// Runs dynamic imGui code
