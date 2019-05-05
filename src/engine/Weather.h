#pragma once
#include "../renderer//Model.h"
#include "../renderer//scenegraph/GeometryNode.h"
#include "..//renderer/scenegraph/GroupNode.h"

#include "Functions.h"
#include "consts.h"

#include <glm/ext/matrix_transform.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

class Snowflake {
private:
	glm::vec3 rotationSpeed;	// Rotation speed per axis
	glm::vec3 orientation;		// Current orientation
	glm::vec3 location;			// Current orientation
public:
	Snowflake(glm::vec3 loc, glm::vec3 rotation);								// Constructor for snowflake
	void moveSnowflake(int time);												// Moves snowflake based on amount of time
	void renderSnowflake(Scenegraph::GroupNode &node, Renderer::Model &model);	// Render snowflake
	float returnHeight();														// Returns lowest height
	float returnX() { return location.x; };										// Returns starting x
	float returnZ() { return location.z; };										// Returns starting y
};