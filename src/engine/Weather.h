#pragma once
#include "../renderer//Model.h"
#include "Functions.h"
#include "consts.h"
#include <glm/ext/matrix_transform.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

class Snowflake {
private:
	glm::vec3 rotationSpeed;	// Rotation speed per axis
	glm::vec3 cords[4];			// Coordinates
public:
	Renderer::Model returnSnowflake(											// Returns model of snowflake
		std::vector<uint32_t>& indices,											// Indices
		Renderer::Material snowflakeMaterial,									// Material
		Renderer::RenderContext& renderContext);								// Render context
	Snowflake(glm::vec3 loc, glm::vec3 rotation);								// Constructor for snowflake
	void moveSnowflake(double time);											// Moves snowflake based on amount of time
	float returnHeight();														// Returns lowest height
	float returnX() { return cords[3].x; };										// Returns starting x
	float returnZ() { return cords[3].z; };										// Returns starting y
};
