#pragma once

const int SIZE_ENVIORMENT = 150;				// Number of points
const int SIZE_ZONES = 15;						// How many zones are SIZE_ENVIORMENT divided into
const float SIZE_TERRAIN = 5.0f;				// The size of triangles
const float HEIGHT_TERRAIN = 0.3f;				// Height of terrain per level
const float MAX_HEIGHT = 255;					// Maximum height
const float HEIGHT_STAGES[] = {					// Height stages(multiplies of max height)
	0.1, 
	0.2,
	0.4,
	0.8
}
