#pragma once
#include "../renderer//Model.h"
#include "Functions.h"
#include "consts.h"

class Snowflake {
private:
	glm::vec3 rotationSpeed;	// Rotation speed per axis
	glm::vec3 cords[4];			// Coordinates
public:
	Renderer::Model returnSnowflake(std::vector<Renderer::Vertex>& vertices,	// Returns model of snowflake
		std::vector<uint32_t>& indices,											// Indices
		Renderer::Material& snowflakeMaterial,									// Material
		Renderer::RenderContext& renderContext);								// Render context
	Snowflake(glm::vec3 loc, glm::vec3 rotation);					// Constructor for snowflake
};
