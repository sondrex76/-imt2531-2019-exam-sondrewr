#include "Weather.h"

// Returns model of snowflake with correct normals
Renderer::Model Snowflake::returnSnowflake(std::vector<Renderer::Vertex>& vertices, std::vector<uint32_t>& indices, Renderer::Material& snowflakeMaterial, Renderer::RenderContext& renderContext) {
	glm::vec3 cords[4] = {
		location, 
		location + direction1 * SIZE_SNOWFLAKE, 
		location + direction2 * SIZE_SNOWFLAKE,
		location + direction2 * SIZE_SNOWFLAKE + direction1 * SIZE_SNOWFLAKE};

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
}


Snowflake::Snowflake(glm::vec3 loc, glm::vec3 dir1, glm::vec3 dir2) {
	location = loc;
	direction1 = glm::normalize(dir1);
	direction2 = glm::normalize(dir2);
}