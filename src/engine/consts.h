#pragma once

#include "../renderer/RenderContext.h"

const glm::vec3 SUN_LIGHT_COLOR(1, 1, 0.2);
const glm::vec3 PASSIVE_LIGHT_COLOR(0.2, 0.2, 0.2);

const int SIZE_ENVIORMENT = 450;							// Number of points
const int SIZE_DIVIDER = 90;								// Number of points per row
const int SIZE_ZONES = SIZE_ENVIORMENT / SIZE_DIVIDER + 1;	// How many zones are SIZE_ENVIORMENT divided into
const int BUTTON_SIZE = 80;									// Size of ImGui buttons
const int PADDING = 20;										// Size of padding in ImGui
const int DIST_SNOW_SPAWN = 61;								// Max distance from camera snow can spawn

const float SIZE_TERRAIN = 2.0f;							// The size of triangles
const float HEIGHT_TERRAIN = 1.0f;							// Height of terrain per level
const float MAX_HEIGHT = 257;								// Maximum height
const float SENSITIVITY = 0.005;							// Camera sensitivity
const float MAX_ANGLE_VERTICAL = 0.8f;						// Max angle down and up
const float MOVEMENT_SPEED = 10;							// Movement speed
const float DISTANCE_LIGHT_SPAWN = 50;						// Distance from camera light source spawns
const float SIZE_SNOWFLAKE = 1.0f;							// Size of snowflake
const float SPEED_SNOWFLAKE = 0.1f;							// Default speed of snowflake
const float GRAVITY = 0.05;									// Strength of gravity
const float DEER_UPWARDS_MOVEMENT = 0.12;					// Speed deer moved up slopes
const float DEER_SPEED = 0.2;								// Speed of deer
const float DEER_MENU_SPEED_MULT = 20;						// Speed mult of deer for menu
const float DEER_SCALE = 1.0f;								// Scale of deer
const float WAIT_TIME_SNOW = 300;							// Waiting time snow
const float DEER_FIRST_HEIGHT_OFFSET = 6;					// y offset in camera height in first person
const float DEER_THIRD_HEIGHT_OFFSET = 10;					// y offset in camera height in third person
const float ALLOWED_VARIANCE_DOWN = 1;						// Distance at which the height is not corrected
const float ALLOWED_VARIANCE_UP = 0.1;						// Distance at which the height is not corrected

const float SNOW_SPAWN_HEIGHT = SIZE_TERRAIN * HEIGHT_TERRAIN * MAX_HEIGHT;

const long long MIN_TIME_CAMERA = 200;						// Minimum time that must have passed between camera switching

const float HEIGHT_STAGES[] = {								// Height stages(multiplies of max height)
	0.0008,
	0.025,
	0.16,
	0.20
};

enum camera {freeCamera, firstCamera, thirdCamera};