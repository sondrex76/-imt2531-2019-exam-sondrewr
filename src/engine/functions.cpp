#include "Functions.h"

glm::vec3 getNormals(glm::vec3 x, glm::vec3 y, glm::vec3 z) {
	glm::vec3 u = y - x, v = z - x;

	return glm::normalize(glm::vec3((u.y * v.z) - (u.z * v.y), (u.z * v.x) - (u.x * v.z), abs(u.x * v.y) - (u.y * v.x)));
}

float getHeight(glm::vec3 x, glm::vec3 y, glm::vec3 z) {
	return (x.y + y.y + x.y) / 3;
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