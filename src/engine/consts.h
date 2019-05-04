#pragma once

const int SIZE_ENVIORMENT = 400;				// Number of points
const int SIZE_ZONES = 41;						// How many zones are SIZE_ENVIORMENT divided into
const float SIZE_TERRAIN = 4.0f;				// The size of triangles
const float HEIGHT_TERRAIN = 0.5f;				// Height of terrain per level
const float MAX_HEIGHT = 127;					// Maximum height
const float HEIGHT_STAGES[] = {					// Height stages(multiplies of max height)
	0.02,
	0.05,
	0.1,
	0.15
};
