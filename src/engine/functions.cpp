#include "Functions.h"

glm::vec3 getNormals(glm::vec3 x, glm::vec3 y, glm::vec3 z) {
	glm::vec3 u = y - x, v = z - x;

	return glm::normalize(glm::vec3((u.y * v.z) - (u.z * v.y), (u.z * v.x) - (u.x * v.z), abs(u.x * v.y) - (u.y * v.x)));
}

float getHeight(glm::vec3 x, glm::vec3 y, glm::vec3 z) {
	return (x.y + y.y + x.y) / 3;
}

glm::vec2 textureOffset(float height) {
	float tallestValue = MAX_HEIGHT * HEIGHT_TERRAIN * SIZE_TERRAIN;
	if (height < HEIGHT_STAGES[0])		// Water
		return glm::vec2(0, 0.25);
	else if (height < HEIGHT_STAGES[1])	// Sand
		return glm::vec2(0, 0);
	else if (height < HEIGHT_STAGES[2])	// Earth
		return glm::vec2(0.25, 0);
	else if (height < HEIGHT_STAGES[3])	// Dirt
		return glm::vec2(0.5, 0);
	else
		return glm::vec2(0.75, 0);		// Snow
}