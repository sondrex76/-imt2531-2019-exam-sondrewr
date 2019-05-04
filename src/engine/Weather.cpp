#include "Weather.h"

// Returns model of snowflake with correct normals
Renderer::Model Snowflake::returnSnowflake(std::vector<Renderer::Vertex>& vertices, std::vector<uint32_t>& indices, Renderer::Material& snowflakeMaterial, Renderer::RenderContext& renderContext) {
	glm::vec3 normal = getNormals(cords[0], cords[1], cords[4]); // Normal for side 2

	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[0]}, /*norm*/normal, /*uv*/{0, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[1]}, /*norm*/normal, /*uv*/{0, 1} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[4]}, /*norm*/normal, /*uv*/{1, 1} });

	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[4]}, /*norm*/normal, /*uv*/{0, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[2]}, /*norm*/normal, /*uv*/{0, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[0]}, /*norm*/normal, /*uv*/{0, 0} });

	normal = getNormals(cords[4], cords[2], cords[0]); // Normal for side 2

	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[4]}, /*norm*/normal, /*uv*/{0, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[1]}, /*norm*/normal, /*uv*/{0, 1} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[0]}, /*norm*/normal, /*uv*/{1, 1} });

	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[0]}, /*norm*/normal, /*uv*/{0, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[2]}, /*norm*/normal, /*uv*/{0, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[4]}, /*norm*/normal, /*uv*/{0, 0} });

	Renderer::Model snowflakeModel = Renderer::Model::fromGeometry(&vertices[0], 12, &indices[0], indices.size(), std::move(snowflakeMaterial), renderContext);

	return snowflakeModel;
}


Snowflake::Snowflake(glm::vec3 coordinates, glm::vec3 rotation) {
	rotationSpeed = rotation;
	cords[0] = coordinates;
	cords[1] = coordinates + glm::vec3(SIZE_SNOWFLAKE, 0, 0);
	cords[2] = coordinates + glm::vec3(0, SIZE_SNOWFLAKE, 0);
	cords[3] = coordinates + glm::vec3(SIZE_SNOWFLAKE), SIZE_SNOWFLAKE, 0;
}

void Snowflake::moveSnowflake(double time) {
	glm::mat4x4 mult = glm::rotate(
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

	cords[0] = glm::vec4(cords[0], 0) * mult;
	cords[1] = glm::vec4(cords[1], 0) * mult;
	cords[2] = glm::vec4(cords[2], 0) * mult;
	cords[3] = glm::vec4(cords[3], 0) * mult;
}