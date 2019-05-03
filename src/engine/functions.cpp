#include "Functions.h"

glm::vec3 getNormals(glm::vec3 x, glm::vec3 y, glm::vec3 z) {
	glm::vec3 u = y - x, v = z - x;

	return glm::normalize(glm::vec3((u.y * v.z) - (u.z * v.y), (u.z * v.x) - (u.x * v.z), abs(u.x * v.y) - (u.y * v.x)));
}