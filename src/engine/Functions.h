#pragma once

#include "../renderer/RenderContext.h"
#include "consts.h"
// Class with general functions

glm::vec3 getNormals(glm::vec3 x, glm::vec3 y, glm::vec3 z);	// Returns the normal of the triangle
void switchIfNotOrdered(float & first, float & second);			// Switches the values if first is smaller then second
float getHeight(glm::vec3 x, glm::vec3 y, glm::vec3 z);			// Returns highest height of vertex
glm::vec2 textureOffset(float height);							// Returns the texture offset based on height