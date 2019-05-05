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