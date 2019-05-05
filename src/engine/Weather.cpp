#include "Weather.h"
#include <iostream>

Snowflake::Snowflake(glm::vec3 coordinates, glm::vec3 rotation) {
	rotationSpeed = rotation;
	orientation = glm::vec3(1, 1, 1);
	location = coordinates;
}

void Snowflake::moveSnowflake(long long time) {
	/*
	glm::mat4x4 rotationMatrix = glm::rotate(
		glm::mat4x4(1.f),
		(float)(rotationSpeed.x * M_PI / 180.f * SPEED_SNOWFLAKE),	// x
		glm::vec3(1, 0, 0)
	) * glm::rotate(
		glm::mat4x4(1.f),
		(float)(rotationSpeed.y * M_PI / 180.f * SPEED_SNOWFLAKE),	// y
		glm::vec3(0, 1, 0)
	) * glm::rotate(
		glm::mat4x4(1.f),
		(float)(rotationSpeed.z * M_PI / 180.f * SPEED_SNOWFLAKE),	// z
		glm::vec3(0, 0, 1));
		*/
	// TODO: make rotation work
	// orientation = glm::vec4(orientation, 0) * rotationMatrix;

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

Renderer::Model getSnowModel(Renderer::RenderContext &renderContext) {
	Renderer::ImageTexture snowflakeTexture(Renderer::ImageTexture::fromFile("resources/Textures/Snowflake.png"));
	Renderer::Material snowflakeMaterial(Renderer::Material(std::move(snowflakeTexture), glm::vec3(0.1, 0.1, 0.1), 32.0f, glm::vec3(0, 0, 0)));

	std::vector<uint32_t> indices;						// indices
	std::vector<Renderer::Vertex> vertices;				// vector with vertexes
	int numIndices = 0;									// Number of indices

	for (int i = 0; i < 12; i++)						// Generates the indices for the four triangles
		indices.push_back(numIndices++);

	// Snowflake model
	glm::vec3 cords[4];
	glm::vec3 coordinates = glm::vec3(0, 0, 0);

	vertices.clear(); // clears vertices

	// Defines coordinates of corners for snowflake
	cords[0] = coordinates + glm::vec3(SIZE_SNOWFLAKE, SIZE_SNOWFLAKE, 0);
	cords[1] = coordinates + glm::vec3(SIZE_SNOWFLAKE, 0, 0);
	cords[2] = coordinates + glm::vec3(0, SIZE_SNOWFLAKE, 0);
	cords[3] = coordinates;

	glm::vec3 normal = getNormals(cords[0], cords[1], cords[2]); // Normal for side 2

	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[3]}, /*norm*/normal, /*uv*/{0, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[1]}, /*norm*/normal, /*uv*/{0, 1} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[0]}, /*norm*/normal, /*uv*/{1, 1} });

	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[0]}, /*norm*/normal, /*uv*/{0, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[2]}, /*norm*/normal, /*uv*/{1, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[3]}, /*norm*/normal, /*uv*/{1, 1} });

	normal = getNormals(cords[3], cords[2], cords[0]); // Normal for side 2

	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[0]}, /*norm*/normal, /*uv*/{0, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[1]}, /*norm*/normal, /*uv*/{0, 1} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[3]}, /*norm*/normal, /*uv*/{1, 1} });

	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[3]}, /*norm*/normal, /*uv*/{0, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[2]}, /*norm*/normal, /*uv*/{1, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[0]}, /*norm*/normal, /*uv*/{1, 1} });

	return Renderer::Model::fromGeometry(&vertices[0], 12, &indices[0], indices.size(), std::move(snowflakeMaterial), renderContext);
}
