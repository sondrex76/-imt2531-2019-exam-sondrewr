#pragma once

#include "../renderer/RenderContext.h"

const glm::vec3 SUN_LIGHT_COLOR(1, 1, 0.05);
const glm::vec3 PASSIVE_LIGHT_COLOR(0.2, 0.2, 0.15);

const int SIZE_ENVIORMENT = 400;							// Number of points
const int SIZE_DIVIDER = 40;								// Number of points per row
const int SIZE_ZONES = SIZE_ENVIORMENT / SIZE_DIVIDER + 1;	// How many zones are SIZE_ENVIORMENT divided into

const float SIZE_TERRAIN = 2.0f;							// The size of triangles
const float HEIGHT_TERRAIN = 0.5f;							// Height of terrain per level
const float MAX_HEIGHT = 257;								// Maximum height
const float SENSITIVITY = 0.005;							// Camera sensitivity

const float HEIGHT_STAGES[] = {								// Height stages(multiplies of max height)
	0.02,
	0.06,
	0.1,
	0.15
};
