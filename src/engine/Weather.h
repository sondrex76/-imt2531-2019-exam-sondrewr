#pragma once
#include "../renderer//Model.h"
#include "Functions.h"
#include "consts.h"

class Snowflake {
private:
	glm::vec3 location;
	glm::vec3 direction1, direction2;	// Directions of snowflake, must be 90 degrees compared to each other
public:
	Renderer::Model returnSnowflake(std::vector<Renderer::Vertex>& vertices,	// Returns model of snowflake
		std::vector<uint32_t>& indices,											// Indices
		Renderer::Material& snowflakeMaterial,									// Material
		Renderer::RenderContext& renderContext);								// Render context
	Snowflake(glm::vec3 loc, glm::vec3 dir1, glm::vec3 dir2);					// Constructor for snowflake
};
