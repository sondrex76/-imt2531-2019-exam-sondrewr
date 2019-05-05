#pragma once

#include "../renderer/RenderContext.h"

const glm::vec3 SUN_LIGHT_COLOR(1, 1, 0.2);
const glm::vec3 PASSIVE_LIGHT_COLOR(0.2, 0.2, 0.2);

const int SIZE_ENVIORMENT = 400;							// Number of points
const int SIZE_DIVIDER = 40;								// Number of points per row
const int SIZE_ZONES = SIZE_ENVIORMENT / SIZE_DIVIDER + 1;	// How many zones are SIZE_ENVIORMENT divided into
const int BUTTON_SIZE = 80;									// Size of ImGui buttons
const int PADDING = 20;										// Size of padding in ImGui

const float SIZE_TERRAIN = 2.0f;							// The size of triangles
const float HEIGHT_TERRAIN = 0.5f;							// Height of terrain per level
const float MAX_HEIGHT = 257;								// Maximum height
const float SENSITIVITY = 0.005;							// Camera sensitivity
const float MAX_ANGLE_VERTICAL = 0.8f;						// Max angle down and up
const float MOVEMENT_SPEED = 10;							// Movement speed
const float DISTANCE_LIGHT_SPAWN = 50;						// Distance from camera light source spawns
const float SIZE_SNOWFLAKE = 1.0f;							// Size of snowflake
const float SPEED_SNOWFLAKE = 0.1f;							// Default speed of snowflake
const float GRAVITY = 10.0f;								// Strength of gravity

const float HEIGHT_STAGES[] = {								// Height stages(multiplies of max height)
	0.002,
	0.03,
	0.1,
	0.15
};
