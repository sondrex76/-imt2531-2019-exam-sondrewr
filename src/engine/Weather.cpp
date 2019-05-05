#include "Weather.h"
#include <iostream>

Snowflake::Snowflake(glm::vec3 coordinates, glm::vec3 rotation) {
	rotationSpeed = rotation;
	orientation = glm::vec3(1, 1, 1);
	location = coordinates;
}

void Snowflake::moveSnowflake(int time) {
	orientation = glm::vec4(orientation, 1) * 
		glm::rotate(
			glm::rotate(
				glm::rotate(
					glm::mat4x4(1.f),
					(float)(rotationSpeed.x * M_PI / 180.f * SPEED_SNOWFLAKE),	// x
					glm::vec3(1, 0, 0)
				),
				(float)(rotationSpeed.y * M_PI / 180.f * SPEED_SNOWFLAKE),		// y
				glm::vec3(0, 1, 0)
			),
			(float)(rotationSpeed.z * M_PI / 180.f * SPEED_SNOWFLAKE),			// z
			glm::vec3(0, 0, 1));


			
	location = location + glm::vec3(0, -time * GRAVITY, 0);
}

void Snowflake::renderSnowflake(Scenegraph::GroupNode &node, Renderer::Model &model) {
	glm::mat4x4 currentLocation =
		glm::translate(
			glm::rotate(
				glm::rotate(
					glm::rotate(
						glm::mat4x4(1.f),
						(float)(orientation.x * M_PI / 180.f),		// Angle to rotate
						glm::vec3(1, 0, 0)							// x
					),
					(float)(orientation.y * M_PI / 180.f),			// Angle to rotate
					glm::vec3(0, 1, 0)								// y
				),
				(float)(orientation.z * M_PI / 180.f),				// Angle to rotate
				glm::vec3(0, 0, 1)									// z
			),
			location												// Offset/Coordinates
		);

	node.addNode(std::make_unique<Scenegraph::GeometryNode>(model, currentLocation));
}

float Snowflake::returnHeight() {
	float currentSelection = location.y; // should probably take into account the direction of the snowflake

	return currentSelection;
}