#include "Functions.h"

glm::vec3 getNormals(glm::vec3 x, glm::vec3 y, glm::vec3 z) {
	glm::vec3 u = y - x, v = z - x;

	return glm::normalize(glm::vec3((u.y * v.z) - (u.z * v.y), (u.z * v.x) - (u.x * v.z), abs(u.x * v.y) - (u.y * v.x)));
}

void switchIfNotOrdered(float & first, float & second) {
	if (first < second) {
		float temp = first;
		first = second;
		second = temp;
	}
}

float getHeight(glm::vec3 x, glm::vec3 y, glm::vec3 z) {
	// Returns highest y value

	// Gets the relevant values
	float heights[3] = {x.y, y.y, z.y};

	switchIfNotOrdered(heights[0], heights[1]);
	switchIfNotOrdered(heights[1], heights[2]);
	switchIfNotOrdered(heights[0], heights[1]);

	return (heights[0] * 0.9 + heights[1] * 0.1);
}

glm::vec2 textureOffset(float height) {
	// Calculates highest value
	float tallestValue = MAX_HEIGHT * HEIGHT_TERRAIN * SIZE_TERRAIN;

	if (height < HEIGHT_STAGES[0] * tallestValue)		// Water
		return glm::vec2(0.8, 0);
	else if (height < HEIGHT_STAGES[1] * tallestValue)	// Sand
		return glm::vec2(0.6, 0);
	else if (height < HEIGHT_STAGES[2] * tallestValue)	// Earth
		return glm::vec2(0.4, 0);
	else if (height < HEIGHT_STAGES[3] * tallestValue)	// Dirt
		return glm::vec2(0.2, 0);
	else
		return glm::vec2(0.0, 0);		// Snow
}

// Checks if value is nor smaller then 0 and that it is smaller then the maximum size of the map
bool validLocation(double location) {
	location /= SIZE_TERRAIN;

	return (location >= 0 && location < SIZE_ENVIORMENT);
}

Renderer::Model getSnowModel(Renderer::RenderContext &renderContext) {
	Renderer::ImageTexture snowflakeTexture(Renderer::ImageTexture::fromFile("resources/Textures/Snowflake.png"));
	Renderer::Material snowflakeMaterial(Renderer::Material(std::move(snowflakeTexture), glm::vec3(0.0001, 0.0001, 0.0001), 0.001f, glm::vec3(0, 0, 0)));

	std::vector<uint32_t> indices;						// indices
	std::vector<Renderer::Vertex> vertices;				// vector with vertexes
	int numIndices = 0;

	numIndices = 0;					// Resets value so it can be used for snowflake
	for (int i = 0; i < 12; i++)	// Goes through the four triangles
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

	normal = getNormals(cords[2], cords[3], cords[0]); // Normal for side 2

	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[0]}, /*norm*/normal, /*uv*/{0, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[1]}, /*norm*/normal, /*uv*/{0, 1} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[3]}, /*norm*/normal, /*uv*/{1, 1} });

	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[3]}, /*norm*/normal, /*uv*/{0, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[2]}, /*norm*/normal, /*uv*/{1, 0} });
	vertices.push_back(Renderer::Vertex{ /*pos*/{cords[0]}, /*norm*/normal, /*uv*/{1, 1} });

	return Renderer::Model::fromGeometry(&vertices[0], 12, &indices[0], indices.size(), std::move(snowflakeMaterial), renderContext);
}
