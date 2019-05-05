#include "Weather.h"
#include <iostream>

Snowflake::Snowflake(glm::vec3 coordinates, glm::vec3 rotation) {
	rotationSpeed = rotation;
	orientation = glm::vec3(0, 0, 0);
	location = coordinates;
}

void Snowflake::moveSnowflake(double time) {
	glm::mat4x4 mult = glm::translate(
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
		glm::vec3(0, 0, 1)), 
		glm::vec3(0, -time * GRAVITY, 0)									// Decreasement in height according to gravity
	);

}

void Snowflake::renderSnowflake(Scenegraph::GroupNode &node, Renderer::Model &model) {
	glm::mat4x4 location =
		glm::translate(
			glm::rotate(
				glm::mat4x4(1.f),
				(float)(90.f * M_PI / 180.f),		// Angle to rotate
				glm::vec3(0, 1, 0)					// Axis to rotate around
			),
			glm::vec3(1, 1, 1)					// Offset/Coordinates
		);

	node.addNode(std::make_unique<Scenegraph::GeometryNode>(model, location));
}

float Snowflake::returnHeight() {
	float currentSelection = location.y; // should probably take into account the direction of the snowflake

	return currentSelection;
}